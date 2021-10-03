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

    void setCameraType(const std::string& maker = "general", const std::string& type = "usb");
    void startCamera(int deviceId, int delay);
    void stopCamera();
    CameraFrameReader::FrameDesc fetchFrame();
};