#pragma once

#include "camera_frame_reader.h"


#include <string>
#include <thread>
#include <future>


class CameraController {

    CameraFrameReader* frameReader_ {nullptr};
    std::thread* workerThread_ {nullptr};
    std::future<int> result_;

public:
    CameraController();
    ~CameraController();

    CameraController(const CameraController&) = delete;
    CameraController& operator=(const CameraController&) = delete;
    CameraController(CameraController&&) = default;
    CameraController& operator=(CameraController&&) = default;

    int width() const;
    int height() const;
    int channels() const;
    size_t memSizePerLine() const;
    size_t memDataSize() const;
    int ndim() const;
    std::vector<int> shape() const;
    std::vector<int> strides() const;

    void setCameraType(const std::string& maker = "general", const std::string& type = "usb");
    bool startCamera(int deviceId, int delay);
    void stopCamera();
    CameraFrameReader::FrameDesc fetchFrame();
    
};