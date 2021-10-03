#include "camera_frame_reader.h"

#include <cstdio>
#include <cstring>

// -------------------------- CameraFrameReader --------------------------


//////////////////////////////////////////////////////////
// ctor/dtor
//////////////////////////////////////////////////////////
CameraFrameReader::CameraFrameReader()
    : deviceId_(-1)
    , delay_(0)
    , fps_(0)
    , width_(0)
    , height_(0)
    , channels_(0)
    , memSizePerLine_(0)
    , memDataSize_(0) {}

CameraFrameReader::~CameraFrameReader() {}

//////////////////////////////////////////////////////////
// private method
//////////////////////////////////////////////////////////
void CameraFrameReader::spin() {

    // std::this_thread::sleep_for(milliseconds(delay_));

    auto abs_time = high_resolution_clock::now() + microseconds(delay_);
    // std::this_thread::sleep_until(abs_time);

    while (high_resolution_clock::now() < abs_time) {
        ; // busy loop
    }
}

//////////////////////////////////////////////////////////
// protected method
//////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////
// public method
//////////////////////////////////////////////////////////
int CameraFrameReader::width() const { return width_; }
int CameraFrameReader::height() const { return height_; }
int CameraFrameReader::channels() const { return channels_; }
size_t CameraFrameReader::sizePerLine() const { return memDataSize_; }

std::vector<int> CameraFrameReader::shape() const {
    std::vector<int> shape = { height_, width_, channels_ };
    return shape;
}

std::vector<int> CameraFrameReader::strides() const {
    auto sh = shape();
    std::vector<int> st(sh.size(), 1);
    for (int i = st.size() - 1; i > 0; --i) {
        st[i-1] = st[i] * sh[i];
    }
    return st;
}


void CameraFrameReader::setDeviceId(int deviceId) {
    deviceId_ = deviceId;
}

int CameraFrameReader::getDeviceId() const {
    return deviceId_;
}

void CameraFrameReader::setDelay(int delay) {
    delay_ = delay;
}

int CameraFrameReader::getDelay() const {
    return delay_;
}

void CameraFrameReader::stop() {
    isRunning_ = false;
}

void CameraFrameReader::start(std::promise<int> result) {
    /* ワーカースレッド側で処理される */

    if (!isInitialized_) {
        std::printf("No initialization.\n");
        return;
    }

    bool status;
    isRunning_ = true;
    high_resolution_clock::time_point tp_start;
    high_resolution_clock::time_point tp_end;
    

    try {
        while (isRunning_) {
            tp_start = high_resolution_clock::now();

            // クリティカルセクション
            {
                std::lock_guard<std::mutex> locker(mtx_);
                status = capture();
            }
            
            if (!status) {
                std::printf("Miss frame!\n");
            }

            // spin(); // フレーム読み込みループを遅延させる
            // auto abs_time = high_resolution_clock::now() + microseconds(delay_);
            // while (high_resolution_clock::now() < abs_time) {
            //     ; // busy loop
            // }
            // std::printf("delay %d\n", delay_);
            // for (int i = 0; i < 10000000; ++i) {
            //     ;
            // }
            std::this_thread::sleep_for(milliseconds(delay_));


            tp_end = high_resolution_clock::now();
            auto msec = duration_cast<milliseconds>(tp_end - tp_start).count();
            fps_ = 1000.0f / msec;

            std::printf("CaptureLoop: %ld[ms], fps: %f \n", msec, fps_);


        }
        result.set_value(0);
    }
    catch (...) {
        // 全例外を捕まえて promiseにセットする
        result.set_exception(std::current_exception());
    }
}

std::function<void(std::promise<int>)> CameraFrameReader::wrapedStart() {
    return [this](std::promise<int> result) -> void {
        this->start(std::move(result));
    };
}

CameraFrameReader::FrameDesc CameraFrameReader::retrieveFrame() const {
    // クリティカルセクション
    using byte = unsigned char;

    std::lock_guard<std::mutex> locker(mtx_);

    std::vector<byte> pickupImgArray(memDataSize_, 0); 
    float fps;

    // deepcopy
    std::memcpy(pickupImgArray.data(), framePtr_, memDataSize_);
    fps = fps_;

    return std::make_tuple(pickupImgArray, fps);
}



// Interface
bool CameraFrameReader::initialize() {
    return this->initializeImpl();
}


// Interface
void CameraFrameReader::release() {
    this->releaseImpl();
}


// Interface
bool CameraFrameReader::capture() {
    return this->captureImpl();
}



// -------------------------- UsbCameraFrameReader --------------------------

//////////////////////////////////////////////////////////
// ctor/dtor
//////////////////////////////////////////////////////////
UsbCameraFrameReader::UsbCameraFrameReader() 
    : CameraFrameReader() {}


UsbCameraFrameReader::~UsbCameraFrameReader() {
    release();
    std::printf("Dtor of UsbCameraFrameReader\n");
}


//////////////////////////////////////////////////////////
// private method
//////////////////////////////////////////////////////////
bool UsbCameraFrameReader::initializeImpl() {

    if (isInitialized_) {
        std::printf("Already initialized.\n");
        return false;
    }

    if (getDeviceId() < 0) {
        std::printf("Please set device id.\n");
        return false;
    }

    std::printf("[Enter] >>> Initialize\n");
    std::printf("Device Id: %d\n", getDeviceId());
 
    capPtr_ = new cv::VideoCapture(getDeviceId(), cv::CAP_V4L2); // cv::CAP_GSTREAMER
    if (!capPtr_->isOpened()) {
        std::printf("[Error] Can not open cv::VideoCapture.\n");
        std::printf("[Exit] <<< Initialize\n");
        delete capPtr_; capPtr_ = nullptr;
        return false;
    }

    std::printf("Success to initialize usb camera with device id: %d\n", 
        getDeviceId());

    std::string backApiStr = capPtr_->getBackendName();
    std::printf("Background api: %s\n", backApiStr.c_str());

    // GStreamerだと設定が反映されない仕様らしい
    // https://qiita.com/iwatake2222/items/b8c442a9ec0406883950
    // capPtr_->set(cv::CAP_PROP_FRAME_WIDTH, 640);
    // capPtr_->set(cv::CAP_PROP_FRAME_HEIGHT, 480);

    auto width = capPtr_->get(cv::CAP_PROP_FRAME_WIDTH);
    auto height = capPtr_->get(cv::CAP_PROP_FRAME_HEIGHT);
    auto fps = capPtr_->get(cv::CAP_PROP_FPS);
    std::printf("Fps: %f, Width: %d, Height: %d\n", fps, (int)width, (int)height);

    // capPtr_->set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('H', '2', '6', '4'));
    // capPtr_->set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
    char forcc[4];
    int symbol = (int)capPtr_->get(cv::CAP_PROP_FOURCC);
    for (int i = 0; i < 4; ++i) {
        forcc[i] = (char)(symbol >> 8 * i) & 0xff;
    }
    std::printf("FourCC: %c%c%c%c\n", forcc[0], forcc[1], forcc[2], forcc[3]);

    
    if (capPtr_->read(cvFrame)) {
        width_ = cvFrame.cols;
        height_ = cvFrame.rows;
        channels_ = cvFrame.channels();
        memSizePerLine_ = cvFrame.step;
        memDataSize_ = height_ * memSizePerLine_;
        std::printf("Retrieve frame: (H, W, C) = (%d, %d, %d)\n", height_, width_, channels_);

        // Frame画像のメモリ確保
        framePtr_ = (byte *)std::malloc(memDataSize_);
        std::memset(framePtr_, 0, memDataSize_);
        std::printf("Malloc framePtr_. Address: %p. Bytesize: %ld\n", 
            (void *)framePtr_, memDataSize_);
    }
    else {
        std::printf("[Error] Can not read frame.\n");
        std::printf("[Exit] <<< Initialize\n");
        delete capPtr_; capPtr_ = nullptr;
        return false;
    }

    isInitialized_ = true; // 初期化完了フラグ

    std::printf("[Exit] <<< Initialize\n");
   
    return true;
}


//////////////////////////////////////////////////////////
// protected method
//////////////////////////////////////////////////////////

void UsbCameraFrameReader::releaseImpl() {
    if (isInitialized_) {
        std::printf("[Enter] >>> Release\n");
        capPtr_->release(); // OpenCV release
        delete capPtr_; capPtr_ = nullptr;
        isInitialized_ = false;
        std::free(framePtr_); framePtr_ = nullptr;
        std::printf("Success to release.\n");
        std::printf("[Exit] <<< Release\n");
    }
}

bool UsbCameraFrameReader::captureImpl() {

    auto start = high_resolution_clock::now();
    bool bret = capPtr_->read(cvFrame);
    auto end = high_resolution_clock::now();
    auto msec = duration_cast<milliseconds>(end - start).count();
    std::printf("Read elapsed time: %ld[ms]\n", msec);
    
    if (bret) {

        if (channels_ == 3) {
            cv::cvtColor(cvFrame, cvFrame, cv::COLOR_BGR2RGB);
        }
        else if (channels_ == 4) {
            cv::cvtColor(cvFrame, cvFrame, cv::COLOR_BGRA2RGBA);
        }

        if (cvFrame.isContinuous()) {
            // 連続メモリ

            // deepcopy
            std::memcpy(framePtr_, cvFrame.data, memDataSize_);
        }
        else {
            // 非連続メモリ(各行間にギャップがある)
            size_t memLine = 0;
            for (int y = 0; y < height_; ++y) {
                // 行単位でdeepcopy
                std::memcpy((void *)&framePtr_[memLine], 
                    (void *)cvFrame.row(y).data, memSizePerLine_);
                memLine += memSizePerLine_;
            }
        }
    }

    return bret;
}

//////////////////////////////////////////////////////////
// public method
//////////////////////////////////////////////////////////