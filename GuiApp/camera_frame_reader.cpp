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
    , fps_(0.0)
    , elapsedTime_(0.0)
    , width_(0)
    , height_(0)
    , channels_(0)
    , memSizePerLine_(0)
    , memDataSize_(0) {}

CameraFrameReader::~CameraFrameReader() {}

//////////////////////////////////////////////////////////
// private method
//////////////////////////////////////////////////////////
void CameraFrameReader::spin() const {
    std::this_thread::sleep_for(milliseconds(delay_));
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
size_t CameraFrameReader::memSizePerLine() const { return memSizePerLine_; }
size_t CameraFrameReader::memDataSize() const { return memDataSize_; }


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
    // std::deque<float> elapsedTimeSeq(100, 0.0);

    try {
        while (isRunning_) {
            auto tp_start = high_resolution_clock::now();

            spin(); // フレーム読み込みループを遅延させる
            {
                // クリティカルセクション
                std::lock_guard<std::mutex> locker(mtx_);
                status = capture();
            }
             
            if (!status) {
                std::printf("Miss frame!\n");
            }
    
            auto tp_end = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(tp_end - tp_start).count() / 1000.0f;

            elapsedTime_ = duration;
            fps_ = 1000.0f / elapsedTime_;

            std::printf("CaptureLoop: %f[ms]\n", duration);
        }
        result.set_value(0);
    }
    catch (...) {
        // 全例外を捕まえて promiseにセットする
        result.set_exception(std::current_exception());
    }
}

CameraFrameReader::FrameDesc CameraFrameReader::retrieveFrame() const {
    // クリティカルセクション
    using byte = unsigned char;

    // std::printf("check\n");
    std::lock_guard<std::mutex> locker(mtx_);

    std::vector<byte> pickupImgArray(memDataSize_, 0); 
    float fps, elapsedTime;

    // deepcopy
    std::memcpy(pickupImgArray.data(), framePtr_, memDataSize_);
    fps = fps_; elapsedTime = elapsedTime_;
    // std::printf("check\n");

    return std::make_tuple(pickupImgArray, fps, elapsedTime);
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
 
    capPtr_ = new cv::VideoCapture(getDeviceId());
    if (!capPtr_->isOpened()) {
        std::printf("[Error] Can not open cv::VideoCapture.\n");
        std::printf("[Exit] <<< Initialize\n");
        delete capPtr_; capPtr_ = nullptr;
        return false;
    }

    std::printf("Success to initialize usb camera with device id: %d\n", getDeviceId());

    std::string backApiStr = capPtr_->getBackendName();
    std::printf("Background api: %s\n", backApiStr.c_str());
    
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
        std::printf("Malloc framePtr_. Address: %p. Bytesize: %ld\n", (void *)framePtr_, memDataSize_);
    }
    else {
        std::printf("[Error] Can not read frame.\n");
        std::printf("[Exit] <<< Initialize\n");
        delete capPtr_; capPtr_ = nullptr;
        return false;
    }

    isInitialized_ = true; // 初期化完了フラグ

    std::printf("[Exit] <<< Initialize\n");
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

    bool bret = capPtr_->read(cvFrame);
    
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
                std::memcpy((void *)&framePtr_[memLine], (void *)cvFrame.row(y).data, memSizePerLine_);
                memLine += memSizePerLine_;
            }
        }
    }

    return bret;
}

//////////////////////////////////////////////////////////
// public method
//////////////////////////////////////////////////////////