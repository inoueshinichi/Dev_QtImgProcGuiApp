#pragma once


#include <deque>
#include <tuple>
#include <vector>
#include <map>
#include <future>
#include <mutex>
#include <functional>
#include <stdexcept> 
#include <exception> // current_exception/rethrow_exception
#include <chrono>
using namespace std::chrono;
#include <memory>

/**
 * @brief カメラフレーム読み取り基底クラス
 * 
 */
class CameraFrameReader : public std::enable_shared_from_this<CameraFrameReader> {
public:
    using byte = unsigned char;
    using FrameDesc = std::tuple<std::vector<byte>, float>; // Image, Fps
    using Shape_t = std::vector<int>;

protected:

    // 画像
    byte *framePtr_ {nullptr}; // (H, W, C)
    int width_;
    int height_;
    int channels_;
    size_t memSizePerLine_;
    size_t memDataSize_;
    
    Shape_t shape_;
    Shape_t strides_;
    int ndim_;

    // 制御
    mutable std::mutex mtx_;
    bool isInitialized_ {false};
    bool isRunning_ {false};
    int deviceId_;
    int delay_; // ms
    float fps_;

private:
    void spin(const high_resolution_clock::time_point& tp_base);

public:
    CameraFrameReader();
    virtual ~CameraFrameReader();

    int width() const;
    int height() const;
    int channels() const;
    size_t memSizePerLine() const;
    size_t memDataSize() const;

    std::vector<int> shape() const;
    std::vector<int> strides() const;
    int ndim() const;

    bool isRunning() const;

    void setDeviceId(int deviceId);
    int  getDeviceId() const;
    void setDelay(int delay);
    int  getDelay() const;
    void stop();
    void start(std::promise<int> result); // フレーム読み込みループ
    std::function<void(std::promise<int>)> wrapedStart();

    FrameDesc retrieveFrame() const;

    // Interface
    bool initialize();
    void release();
    bool capture();

protected:
    virtual bool initializeImpl() = 0;
    virtual void releaseImpl() = 0;
    virtual bool captureImpl() = 0;
};



#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>

class cv::VideoCapture;

/**
 * @brief USBカメラフレーム取り込みクラス
 * 
 */
class UsbCameraFrameReader : public CameraFrameReader {
    cv::VideoCapture* capPtr_;
    cv::Mat cvFrame;

public:
    UsbCameraFrameReader();
    virtual ~UsbCameraFrameReader();

protected:
    bool initializeImpl() override final;
    void releaseImpl() override final;
    bool captureImpl() override final;
};