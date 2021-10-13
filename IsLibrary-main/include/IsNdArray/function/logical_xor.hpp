#pragma once

#include <IsNdArray/function/utils/base_transform_binary.hpp>

#include <cmath>

namespace is
{
    namespace nbla
    {
        NBLA_DEFINE_TRANSFORM_BINARY(LogicalXor, (bool(x0) ^ bool(x1)))
    }
}