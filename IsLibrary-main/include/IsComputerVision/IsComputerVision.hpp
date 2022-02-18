#pragma once

#ifdef _MSC_VER
    // https://qiita.com/Chironian/items/462a3bdf271d5f0b00b6#%EF%BC%92%EF%BC%93c4251%E8%AD%A6%E5%91%8A%E3%81%8C%E5%87%BA%E3%82%8B
    #pragma warning(disable:4251)
#endif

#if defined(_MSC_VER) && !defined(__CUDACC__)
    #if defined(imgproc_EXPORTS) || defined(imgproc_dbg_EXPORTS)
        #define IS_IMGPROC_API __declspec(dllexport)
    #else
        #define IS_IMGPROC_API __declspec(dllimport)
    #endif
#else
    #define IS_IMGPROC_API
#endif

#if _MSC_VER
    #define _USE_MATH_DEFINES
#endif
#include <cmath>

    // C++11 gives alignas as standard
    // http://en.cppreference.com/w/cpp/language/alignas
#define IS_IMGPROC_ALIGN(N) alignas(N)


// Memory
#include <cstring>
#define IS_ZERO_MEMORY(ptr, bytesize) std::memset((void *)ptr, 0, bytesize)



// Log
#if (0)
    #define IS_DEBUG_FLAG 0
    #define IS_DEBUG_STREAM(format, ...)
#else
    #include <cstdio>
    #define IS_DEBUG_FLAG 1
    #define IS_DEBUG_STREAM(format, ...) std::printf(format, ##__VA_ARGS__)
#endif


#define IS_DEBUG_CHECK_NDARRAY_STATE(func, flag, ndarray) \
  if (flag > 0) {                                         \
    auto ndim = ndarray->ndim();                          \
    auto shape = ndarray->shape();                        \
    auto strides = ndarray->strides();                    \
    auto dtype = ndarray->dtype();                        \
    auto type = nbla::dtype_to_string(dtype);             \
    std::ostringstream oss;                               \
    oss << #func << ", ";                                 \
    oss << "Type: " << type << ", ";                      \
    oss << "ndim: " << ndim << ", ";                      \
    oss << "shape: (";                                    \
    for (int d = 0; d < ndim; ++d) {                      \
      oss << shape[d];                                    \
      if (d != ndim - 1) {                                \
        oss << ",";                                       \
      } else {                                            \
        oss << "), ";                                     \
      }                                                   \
    }                                                     \
                                                          \
    oss << "strides: (";                                  \
    for (int d = 0; d < ndim; ++d) {                      \
      oss << strides[d];                                  \
      if (d != ndim - 1) {                                \
        oss << ",";                                       \
      } else {                                            \
        oss << ")";                                       \
      }                                                   \
    }                                                     \
    std::cout << oss.str() << std::endl;                  \
  }


#define IS_CHECK_NDARRAY_SHAPE_AS_IMAGE(ndarray)                                 \
  {                                                                              \
    if (!ndarray.get()) {                                                        \
      throw std::runtime_error("NdArray is nullptr.");                           \
    }                                                                            \
    auto ndim = ndarray->ndim();                                                 \
    auto shape = ndarray->shape();                                               \
    auto strides = ndarray->strides();                                           \
                                                                                 \
    if (ndim != 3) {                                                             \
      throw std::runtime_error(                                                  \
          is::common::format_string("Miss matching 3 ndim. Given is %d", ndim)); \
    } else {                                                                     \
      /*(C, H, W)*/                                                              \
      int channels = shape[0];                                                   \
      if (channels > 3) {                                                        \
        throw std::runtime_error(is::common::format_string(                      \
            "Miss matching channels of top shape (<=3). Given is %d",            \
            channels));                                                          \
      }                                                                          \
    }                                                                            \
  }


#include <IsComputerVision/saturate_cast.hpp>
#include <IsComputerVision/type.hpp>
