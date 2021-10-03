
#include "camera_controller.h"

#include <iostream>

//////////////////////////////////////////////////////////
// ctor/dtor
//////////////////////////////////////////////////////////
CameraController::CameraController() {}


CameraController::~CameraController() {
    if (frameReader_) {
        delete frameReader_;
        frameReader_ = nullptr;
    }

    if (workerThread_) {
        delete workerThread_;
        workerThread_ = nullptr;
    }
}


//////////////////////////////////////////////////////////
// private method
//////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////
// protected method
//////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////
// public method
//////////////////////////////////////////////////////////

int CameraController::width() const { return frameReader_->width(); }
int CameraController::height() const { return frameReader_->height(); }
int CameraController::channels() const { return frameReader_->channels(); }
size_t CameraController::memSizePerLine() const { return frameReader_->memSizePerLine(); }
size_t CameraController::memDataSize() const { return frameReader_->memDataSize(); }


int CameraController::ndim() const { return frameReader_->ndim(); }
std::vector<int> CameraController::shape() const { return frameReader_->shape(); }
std::vector<int> CameraController::strides() const { return frameReader_->strides(); }

void CameraController::setCameraType(const std::string& maker, const std::string& type) {

    if (frameReader_) {
        delete frameReader_;
        frameReader_ = nullptr;
    }

    if (maker == "general") {
        if (type == "usb") {
            frameReader_ = new UsbCameraFrameReader();
        }
        else if (type == "ethernet") {

        }
        else if (type == "wifi") {

        }
    }
    else if (maker == "ids") {

    }
    else if (maker == "omron") {

    }
    else if (maker == "cognex") {

    }
    else if (maker == "baslar") {

    }

    std::printf("maker: %s, type: %s\n", maker.c_str(), type.c_str());
}


bool CameraController::startCamera(int deviceId, int delay) {

    if (!frameReader_) {
        std::printf("No configure frame reader. Please configure maker and type.\n");
        return false;
    }

    frameReader_->setDeviceId(deviceId);
    frameReader_->setDelay(delay);
    if (!frameReader_->initialize()) {
        return false;
    }

    std::promise<int> prms;
    result_ = prms.get_future();
    workerThread_ = new std::thread(frameReader_->wrapedStart(), std::move(prms));
    std::cout << "[Start] worker thread. Thread id: " << workerThread_->get_id() << std::endl;

    return true;
}


void CameraController::stopCamera() {

    if (!workerThread_) {
        std::printf("Don't start worker thread.\n");
        return;
    }

    frameReader_->stop(); // 例外が発生していれば、既にWorkerThreadは動作停止しているかも

    try {
        // 例外のthrowはfuture<T>::get()で起こる
        result_.get();
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl; // WorkerThread内部で発生した例外をキャッチ
    }

    workerThread_->join(); // スレッド終了までメインスレッド側を待機
    frameReader_->release();

    delete workerThread_;
    workerThread_ = nullptr;

    std::printf("[Stop] worker thread.\n");
}



//#define IS_DEBUG_SHOW

CameraFrameReader::FrameDesc CameraController::fetchFrame() {
    using byte = unsigned char;

#ifdef IS_DEBUG_SHOW
    // 時間取得
    char timeString[256];
    std::memset((void *)&timeString, '\0', sizeof(timeString));
    time_t theTime = time(nullptr);
    struct tm *stm = localtime(&theTime);
    if (theTime == -1 || stm == nullptr)
    {
        std::snprintf(timeString, 256, "Unknown");
    }
    else
    {
        strftime(timeString, 256, "%Y-%m-%d %H:%M", stm);
    }

    std::printf("Fetch datetime: %s\n", timeString);
#endif

    if (frameReader_) {
        return frameReader_->retrieveFrame();
    }
    else {
        return std::make_tuple(std::vector<byte>(), 0.0);
    }
}
