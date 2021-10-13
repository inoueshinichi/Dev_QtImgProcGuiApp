#pragma once

/*Context*/
#include <IsNdArray/global_context.hpp>
#include <IsNdArray/singleton_manager.hpp>

/*NdArray*/
#include <IsNdArray/nd_array.hpp>
#include <IsNdArray/nd_array_extra.hpp>

#include <IsComputerVision/IsComputerVision.hpp>

#include <IsCommon/format_string.hpp>
#include <IsCommon/split_string.hpp>
#include <IsCommon/join_string.hpp>

#include <stdexcept>
#include <exception>
#include <cassert>
#include <cmath>
#include <limits>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <cstring>
#include <string>
#include <sstream>

#include <tuple>
#include <vector>
#include <deque>
#include <list>

namespace is {
    namespace imgproc {
        using namespace nbla;

        /**
         * @brief saturate_cast for NdArray
         * 
         * @tparam T 
         * @param src 
         * @return NdArrayPtr 
         */
        template <typename T>
        NdArrayPtr saturate_clamp(NdArrayPtr src) {
            const auto &ctx =
                SingletonManager::get<GlobalContext>()->get_current_context();


#define IS_SATURATE_CAST(dtype, type)                                        \
    case dtypes::dtype:                                                      \
        {                                                                    \
            type *data = src->cast_data_and_get_pointer<type>(ctx);          \
            for (size_t k = 0; k < src->size(); ++k) {                       \
                data[k] = (type)saturate_cast<T>(data[k]);                   \
            }                                                                \
        }                                                                    \
        break

            auto dtype = src->dtype();
            switch (dtype)
            {
                IS_SATURATE_CAST(UBYTE, unsigned char);
                IS_SATURATE_CAST(BYTE, char);
                IS_SATURATE_CAST(USHORT, unsigned short);
                IS_SATURATE_CAST(SHORT, short);
                IS_SATURATE_CAST(UINT, unsigned int);
                IS_SATURATE_CAST(INT, int);
                IS_SATURATE_CAST(ULONG, unsigned long);
                IS_SATURATE_CAST(LONG, long);
                IS_SATURATE_CAST(ULONGLONG, unsigned long long);
                IS_SATURATE_CAST(LONGLONG, long long);
                IS_SATURATE_CAST(FLOAT, float);
                IS_SATURATE_CAST(DOUBLE, double);
                IS_SATURATE_CAST(BOOL, bool);
                IS_SATURATE_CAST(LONGDOUBLE, long double);
            case dtypes::HALF:
                {                                                                    
                    Half *data = src->cast_data_and_get_pointer<Half>(ctx);          
                    for (size_t k = 0; k < src->size(); ++k) {                       
                        data[k] = (Half)saturate_cast<T>((float)data[k]);                   
                    }                                                                
                }       
                break;
            }

            return src;
#undef IS_SATURATE_CAST
        }
    }
}

