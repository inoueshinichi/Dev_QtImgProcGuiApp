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

    namespace is
    {
        namespace imgproc
        {
            // // 前方宣言
            // template <typename T>
            // class Rect_<T>;

            ////////////////////////////////////////////////////
            // Point_ 2次元座標プライマリーテンプレートクラス
            ////////////////////////////////////////////////////
            template <typename T>
            class Point_
            {
            public:
                T x_;
                T y_;

            public:
                Point_() : x_(T(0)), y_(T(0)) {}
                virtual ~Point_() = default;
                Point_(T x, T y) : x_(x), y_(y) {}

                Point_(const Point_<T> &other) = default;
                Point_<T> &operator=(const Point_<T> &other) = default;
                Point_(Point_<T> &&other) = default;
                Point_<T> &operator=(Point_<T> &&other) = default;

                template <typename U>
                operator Point_<U>() const
                {
                    return Point_<U>(saturate_cast<U>(x_), saturate_cast<U>(y_));
                }

                double norm() const
                {
                    return std::sqrt(x_ * x_ + y_ * y_);
                }

                double dot(const Point_<T> &point) const
                {
                    return std::sqrt(x_ * point.x_ + y_ * point.y_);
                }

                // // ポインタ使わないと前方宣言できないからどうやって実現しているかわからない
                // bool inside(const Rect_<T> &rect) const
                // {
                //     return rect.contains(*this);
                // }

                //     /*static operator*/
                //     // 1) Point_<T> &operator+=(Point_<T> &a, const Point_<T> &b);
                //     // 2) Point_<T> &operator-=(Point_<T> &a, const Point_<T> &b);
                //     // 3) Point_<T> &operator*=(Point_<T> &a, U b);
                //     // 4) Point_<T> &operatpr/=(Point_<T> &a, U b);
                //     // 5) bool operator==(const Point_<T> &a, const Point_<T> &b);
                //     // 6) bool operator!=(const Point_<T> &a, const Point_<T> &b);
                //     // 7) Point_<T> operator+(const Point_<T> &a, const Point_<T> &b);
                //     // 8) Point_<T> operator-(const Point_<T> &a, const Point_<T> &b);
                //     // 9) Point_<T> operator*(const Point_<T> &a, U b);
                //     // 10) Point_<T> operator/(const Point_<T> &a, U b);
            };

            /*エイリアス*/
            typedef Point_<int> Point2i;
            typedef Point2i Point;
            typedef Point_<float> Point2f;
            typedef Point_<double> Point2d;

            ////////////////////////////////////////////////////
            // Size_ 縦横プライマリーテンプレートクラス
            ////////////////////////////////////////////////////
            template <typename T>
            class Size_
            {
                T width_;
                T height_;

            public:
                Size_() : width_(T(0)), height_(T(0)) {}
                virtual ~Size_() = default;
                Size_(T width, T height) : width_(width), height_(height) {}
                Size_(const Point_<T> &point) : width_(point.x_), height_(point.y_) {}
                Size_(const Size_<T> &other) = default;
                Size_ &operator=(const Size_<T> &other) = default;
                Size_(Size_<T> &&other) = default;
                Size_ &operator=(Size_<T> &&other) = default;

                T width() const { return width_; }
                T height() const { return height_; }

                T area() const
                {
                    return width_ * height_;
                }
            };

            /*エイリアス*/
            typedef Size_<int> Size;
            typedef Size_<float> Sizef;
            typedef Size_<double> Sized;

            ////////////////////////////////////////////////////
            // Rect_ 2次元領域プライマリーテンプレートクラス
            ////////////////////////////////////////////////////
            template <typename T>
            class Rect_
            {
            public:
                T top_;
                T left_;
                T bottom_;
                T right_;

            public:
                Rect_()
                    : top_(T(0)), left_(T(0)), bottom_(T(0)), right_(T(0)) {}
                virtual ~Rect_() = default;
                Rect_(T x, T y, T width, T height)
                    : top_(y), left_(x), bottom_(y + height), right_(x + width) {}

                Rect_(const Rect_<T> &other) = default;
                Rect_<T> &operator=(const Rect_<T> &other) = default;
                Rect_(Rect_<T> &&other) = default;
                Rect_<T> &operator=(Rect_<T> &&other) = default;

                operator Rect_<int>() const
                {
                    return Rect_<int>(saturate_cast<int>(top_),
                                      saturate_cast<int>(left_),
                                      saturate_cast<int>(bottom_),
                                      saturate_cast<int>(right_));
                }

                operator Rect_<float>() const
                {
                    return Rect_<float>(saturate_cast<float>(top_),
                                        saturate_cast<float>(left_),
                                        saturate_cast<float>(bottom_),
                                        saturate_cast<float>(right_));
                }

                operator Rect_<double>() const
                {
                    return Rect_<double>(saturate_cast<double>(top_),
                                         saturate_cast<double>(left_),
                                         saturate_cast<double>(bottom_),
                                         saturate_cast<double>(right_));
                }

                bool contains(const Point_<T> &point) const;
                T width() const;
                T height() const;
                Point_<T> left_top() const;
                Point_<T> right_bottom() const;
                T area() const
                {
                    return width() * height();
                }
            };

            /*エイリアス*/
            typedef Rect_<int> Rect;
            typedef Rect_<float> Rectf;
            typedef Rect_<double> Rectd;

            ////////////////////////////////////////////////////
            // Point3_ 3次元座標プライマリーテンプレートクラス
            ////////////////////////////////////////////////////
            template <typename T>
            class Point3_
            {
            public:
                T x_;
                T y_;
                T z_;

            public:
                Point3_() : x_(T(0)), y_(T(0)), z_(T(0)) {}
                Point3_(T x, T y, T z) : x_(x), y_(y), z_(z) {}
                virtual ~Point3_() = default;
                // explicit Point3_(const Point_<T> &point)
                //     : x_(point.x_), y_(point.y_), z_(T(0)) {}
                Point3_(const Point3_<T> &other) = default;
                Point3_ &operator=(const Point3_<T> &other) = default;
                Point3_(Point3_<T> &&other) = default;
                Point3_ &operator=(Point3_<T> &&other) = default;

                template <typename U>
                operator Point3_<U>() const
                {
                    return Point3_<U>(saturate_cast<U>(x_),
                                      saturate_cast<U>(y_),
                                      saturate_cast<U>(z_));
                }

                double norm() const
                {
                    return std::sqrt(x_ * x_ + y_ * y_ + z_ * z_);
                }

                double dot(const Point3_<T> &point) const
                {
                    return std::sqrt(x_ * point.x_ + y_ * point.y_ + z_ * point.z_);
                }

                //     /*static operator*/
                //     // 1) Point3_<T> &operator+=(Point3_<T> &a, const Point3_<T> &b);
                //     // 2) Point3_<T> &operator-=(Point3_<T> &a, const Point3_<T> &b);
                //     // 3) Point3_<T> &operator*=(Point3_<T> &a, U b);
                //     // 4) Point3_<T> &operatpr/=(Point3_<T> &a, U b);
                //     // 5) bool operator==(const Point3_<T> &a, const Point3_<T> &b);
                //     // 6) bool operator!=(const Point3_<T> &a, const Point3_<T> &b);
                //     // 7) Point3_<T> operator+(const Point3_<T> &a, const Point3_<T> &b);
                //     // 8) Point3_<T> operator-(const Point3_<T> &a, const Point3_<T> &b);
                //     // 9) Point3_<T> operator*(const Point3_<T> &a, U b);
                //     // 10) Point3_<T> operator/(const Point3_<T> &a, U b);
            };

            /*エイリアス*/
            typedef Point3_<int> Point3i;
            typedef Point3i Point3;
            typedef Point3_<float> Point3f;
            typedef Point3_<double> Point3d;

            ////////////////////////////////////////////////////
            // Voxel_ 3次元領域プライマリーテンプレートクラス
            ////////////////////////////////////////////////////
            template <typename T>
            class Voxel_
            {
                /* 3D Cube
                   p1 ---- p4
                  /|      / |
                p2 ---- p3  |
                |  |    |   |
                |  p5 --|- p8
                | /     |  /
                p6 ---- p7

                @warning
                クラス作ったけど、3D Facetを定義して、
                それをクラスにもたせるようにしないとだめかも.
            */

            public:
                Point3_<T> p1_;
                Point3_<T> p2_;
                Point3_<T> p3_;
                Point3_<T> p4_;
                Point3_<T> p5_;
                Point3_<T> p6_;
                Point3_<T> p7_;
                Point3_<T> p8_;

            public:
                Voxel_() {}
                Voxel_(const Point3_<T> p1,
                       const Point3_<T> p2,
                       const Point3_<T> p3,
                       const Point3_<T> p4,
                       const Point3_<T> p5,
                       const Point3_<T> p6,
                       const Point3_<T> p7,
                       const Point3_<T> p8)
                    : p1_(p1), p2_(p2), p3_(p3), p4_(p4), p5_(p5), p6_(p6), p7_(p7), p8_(p8) {}

                virtual ~Voxel_() = default;

                Voxel_(const Voxel_<T> &other) = default;
                Voxel_ &operator=(const Voxel_<T> &other) = default;
                Voxel_(Voxel_<T> &&other) = default;
                Voxel_ &operator=(Voxel_<T> &&other) = default;
            };
        }
}

/*テンプレート関数の実装*/
#include <IsComputerVision/IsComputerVision-impl.hpp>
