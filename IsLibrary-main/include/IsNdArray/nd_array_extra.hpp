#pragma once

#include <IsNdArray/nd_array.hpp>
#include <IsNdArray/global_context.hpp>

// Generation
#include <IsNdArray/function/rand.hpp>
#include <IsNdArray/function/randint.hpp>
#include <IsNdArray/function/randn.hpp>
#include <IsNdArray/function/arange.hpp>

// PointWise-1
#include <IsNdArray/function/abs.hpp>
#include <IsNdArray/function/exp.hpp>
#include <IsNdArray/function/acos.hpp>
#include <IsNdArray/function/sin.hpp>
#include <IsNdArray/function/asin.hpp>
#include <IsNdArray/function/tan.hpp>
#include <IsNdArray/function/atan.hpp>
#include <IsNdArray/function/sinc.hpp>



// Pointwise-2
#include <IsNdArray/function/add_scalar.hpp>
#include <IsNdArray/function/pow_scalar.hpp>
#include <IsNdArray/function/mul_scalar.hpp>
#include <IsNdArray/function/r_div_scalar.hpp>
#include <IsNdArray/function/r_pow_scalar.hpp>
#include <IsNdArray/function/r_sub_scalar.hpp>

// Ope1
#include <IsNdArray/function/transpose.hpp>
#include <IsNdArray/function/broadcast.hpp>
#include <IsNdArray/function/reshape.hpp>
#include <IsNdArray/function/slice.hpp>

// Reduce
#include <IsNdArray/function/sum.hpp>
#include <IsNdArray/function/mean.hpp>
#include <IsNdArray/function/max.hpp>
#include <IsNdArray/function/min.hpp>
#include <IsNdArray/function/prod.hpp>

// Ope2
#include <IsNdArray/function/sort.hpp>
#include <IsNdArray/function/cumsum.hpp>
#include <IsNdArray/function/cumprod.hpp>





#include <memory>


namespace is
{
    namespace nbla
    {
        // -------------------------------------------------------

        // zeros
        template <typename T>
        NdArrayPtr zeros(const Shape_t& shape)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            auto ndarray = NdArray::create(shape);
            ndarray->zero();
            ndarray->cast_data_and_get_pointer<T>(ctx);
            return ndarray;
        }


        // ones
        template <typename T>
        NdArrayPtr ones(const Shape_t& shape)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            auto ndarray = NdArray::create(shape);
            ndarray->fill(1);
            ndarray->cast_data_and_get_pointer<T>(ctx);
            return ndarray;
        }


        // eye
        template <typename T>
        NdArrayPtr eye(int rows, int cols)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            Shape_t shape{rows, cols};
            auto ndarray = NdArray::create(shape);
            ndarray->zero();
            T* data = ndarray->cast_data_and_get_pointer<T>(ctx);

            Stride_t strides = ndarray->strides();
            int min_len = std::min(rows, cols);
            for (int i = 0; i < min_len; ++i)
            {
                data[i * strides[0] + i * strides[1]] = (T)1;
            }
            return ndarray;
        }

        
        // randn
        template <typename F>
        NdArrayPtr randn(const Shape_t& shape, float mu, float sigma, int seed = -1)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            Randn<F> operation(ctx, mu, sigma, shape, seed);
            auto output = zeros<F>(shape);
            operation.setup({}, {output});
            operation.execute({}, {output});
            return output;
        }


        // rand
        template <typename F>
        NdArrayPtr rand(const Shape_t& shape, float low, float high, int seed = -1)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            Rand<F> operation(ctx, low, high, shape, seed);
            auto output = zeros<F>(shape);
            operation.setup({}, {output});
            operation.execute({}, {output});
            return output;
        }

        // randint
        template <typename T>
        NdArrayPtr randint(const Shape_t &shape, int low, int high, int seed = -1)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            Randint<T> operation(ctx, low, high, shape, seed);
            auto output = zeros<T>(shape);
            operation.setup({}, {output});
            operation.execute({}, {output});
            return output;
        }

        // arange
        template <typename T>
        NdArrayPtr arange(double start, double stop, double step)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            Arange<T> operation(ctx, start, stop, step);
            auto output = NdArray::create();
            output->cast_data_and_get_pointer<T>(ctx);
            operation.setup({}, {output});
            operation.execute({}, {output});
            return output;
        }

        // -------------------------------------------------------

        // abs
        template <typename T>
        NdArrayPtr abs(NdArrayPtr input)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            Abs<T> operation(ctx);
            auto output = NdArray::create();
            output->cast_data_and_get_pointer<T>(ctx);
            operation.setup({input}, {output});
            operation.execute({input}, {output});
            return output;
        }

        // exp
        template <typename T>
        NdArrayPtr exp(NdArrayPtr input)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            Exp<T> operation(ctx);
            auto output = NdArray::create();
            output->cast_data_and_get_pointer<T>(ctx);
            operation.setup({input}, {output});
            operation.execute({input}, {output});
            return output;
        }

        // acos
        template <typename T>
        NdArrayPtr acos(NdArrayPtr input)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            ACos<T> operation(ctx);
            auto output = NdArray::create();
            output->cast_data_and_get_pointer<T>(ctx);
            operation.setup({input}, {output});
            operation.execute({input}, {output});
            return output;
        }

        // sin
        template <typename T>
        NdArrayPtr sin(NdArrayPtr input)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            Sin<T> operation(ctx);
            auto output = NdArray::create();
            output->cast_data_and_get_pointer<T>(ctx);
            operation.setup({input}, {output});
            operation.execute({input}, {output});
            return output;
        }

        // asin
        template <typename T>
        NdArrayPtr asin(NdArrayPtr input)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            ASin<T> operation(ctx);
            auto output = NdArray::create();
            output->cast_data_and_get_pointer<T>(ctx);
            operation.setup({input}, {output});
            operation.execute({input}, {output});
            return output;
        }

        // tan
        template <typename T>
        NdArrayPtr tan(NdArrayPtr input)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            Tan<T> operation(ctx);
            auto output = NdArray::create();
            output->cast_data_and_get_pointer<T>(ctx);
            operation.setup({input}, {output});
            operation.execute({input}, {output});
            return output;
        }

        // atan
        template <typename T>
        NdArrayPtr atan(NdArrayPtr input)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            ATan<T> operation(ctx);
            auto output = NdArray::create();
            output->cast_data_and_get_pointer<T>(ctx);
            operation.setup({input}, {output});
            operation.execute({input}, {output});
            return output;
        }


        // -------------------------------------------------------

        // add_scalar
        template <typename T>
        NdArrayPtr add_scalar(NdArrayPtr input, double val, bool inplace = false)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            AddScalar<T> operation(ctx, val, inplace);
            if (inplace) {
                operation.setup({input}, {input});
                operation.execute({input}, {input});
                return input;
            }
            else {
                auto output = NdArray::create();
                output->cast_data_and_get_pointer<T>(ctx);
                operation.setup({input}, {output});
                operation.execute({input}, {output});
                return output;
            }
        }

        // pow_scalar
        template <typename T>
        NdArrayPtr pow_scalar(NdArrayPtr input, double val, bool inplace = false)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            PowScalar<T> operation(ctx, val, inplace);
            if (inplace) {
                operation.setup({input}, {input});
                operation.execute({input}, {input});
                return input;
            }
            else {
                auto output = NdArray::create();
                output->cast_data_and_get_pointer<T>(ctx);
                operation.setup({input}, {output});
                operation.execute({input}, {output});
                return output;
            }
        }

        // mul_scalar
        template <typename T>
        NdArrayPtr mul_scalar(NdArrayPtr input, double val, bool inplace = false)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            MulScalar<T> operation(ctx, val, inplace);
            if (inplace) {
                operation.setup({input}, {input});
                operation.execute({input}, {input});
                return input;
            }
            else {
                auto output = NdArray::create();
                output->cast_data_and_get_pointer<T>(ctx);
                operation.setup({input}, {output});
                operation.execute({input}, {output});
                return output;
            }
        }

        // r_div_scalar
        template <typename T>
        NdArrayPtr r_div_scalar(NdArrayPtr input, double val, bool inplace = false)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            RDivScalar<T> operation(ctx, val, inplace);
            if (inplace) {
                operation.setup({input}, {input});
                operation.execute({input}, {input});
                return input;
            }
            else {
                auto output = NdArray::create();
                output->cast_data_and_get_pointer<T>(ctx);
                operation.setup({input}, {output});
                operation.execute({input}, {output});
                return output;
            }
        }

        // r_pow_scalar
        template <typename T>
        NdArrayPtr r_pow_scalar(NdArrayPtr input, double val, bool inplace = false)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            RPowScalar<T> operation(ctx, val, inplace);
            if (inplace) {
                operation.setup({input}, {input});
                operation.execute({input}, {input});
                return input;
            }
            else {
                auto output = NdArray::create();
                output->cast_data_and_get_pointer<T>(ctx);
                operation.setup({input}, {output});
                operation.execute({input}, {output});
                return output;
            }
        }

        // r_sub_scalar
        template <typename T>
        NdArrayPtr r_sub_scalar(NdArrayPtr input, double val, bool inplace = false)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            RSubScalar<T> operation(ctx, val, inplace);
            if (inplace) {
                operation.setup({input}, {input});
                operation.execute({input}, {input});
                return input;
            }
            else {
                auto output = NdArray::create();
                output->cast_data_and_get_pointer<T>(ctx);
                operation.setup({input}, {output});
                operation.execute({input}, {output});
                return output;
            }
        }

        // -------------------------------------------------------
        
        // transpose
        template <typename T>
        NdArrayPtr transpose(NdArrayPtr input, const std::vector<int64_t> &axes)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            Transpose<T> operation(ctx, axes);
            auto output = NdArray::create();
            operation.setup({input}, {output});
            operation.execute({input}, {output});
            return output;
        }

        // broadcast
        template <typename T>
        NdArrayPtr broadcast(NdArrayPtr input, const Shape_t& shape)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            Broadcast<T> operation(ctx, shape);
            auto output = NdArray::create();
            operation.setup({input}, {output});
            operation.execute({input}, {output});
            return output;
        }


        // reshape
        template <typename T>
        NdArrayPtr reshape(NdArrayPtr input, const std::vector<int64_t> &shape)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            Reshape<T> operation(ctx, shape, false);
            auto output = NdArray::create();
            operation.setup({input}, {output});
            operation.execute({input}, {output});
            return output;
        }


        // slice
        template <typename T>
        NdArrayPtr slice(NdArrayPtr input, const vector<int64_t> &starts, 
                         const vector<int64_t> &stops, const vector<int64_t> &steps)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            Slice<T> operation(ctx, starts, stops, steps);
            auto output = NdArray::create();
            operation.setup({input}, {output});
            operation.execute({input}, {output});
            return output;
        }

        // ---

        // sum
        template <typename T>
        NdArrayPtr sum(NdArrayPtr input, int axis = 0, bool keep_dims = false)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            Sum<T> operation(ctx, {axis}, keep_dims);
            auto output = NdArray::create();
            operation.setup({input}, {output});
            operation.execute({input}, {output});
            return output;
        }


        // mean
        template <typename T>
        NdArrayPtr mean(NdArrayPtr input, int axis = 0, bool keep_dims = false) 
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            Mean<T> operation(ctx, {axis}, keep_dims);
            auto output = NdArray::create();
            operation.setup({input}, {output});
            operation.execute({input}, {output});
            return output;
        }

        // max
        template <typename T>
        vector<NdArrayPtr> max(NdArrayPtr input, int axis = 0, bool keep_dims = false, bool with_index = false, bool only_index = false) 
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            Max<T> operation(ctx, {axis}, keep_dims, with_index, only_index);

            if (!with_index)
            {
                auto output = NdArray::create();
                operation.setup({input}, {output});
                operation.execute({input}, {output});
                return {output};
            }
            else
            {
                auto output = NdArray::create();
                auto output_index = NdArray::create();
                operation.setup({input}, {output, output_index});
                operation.execute({input}, {output, output_index});
                return {output, output_index};
            }
        }

        // min
        template <typename T>
        vector<NdArrayPtr> min(NdArrayPtr input, int axis = 0, bool keep_dims = false, bool with_index = false, bool only_index = false) 
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            Min<T> operation(ctx, {axis}, keep_dims, with_index, only_index);

            if (!with_index)
            {
                auto output = NdArray::create();
                operation.setup({input}, {output});
                operation.execute({input}, {output});
                return {output};
            }
            else
            {
                auto output = NdArray::create();
                auto output_index = NdArray::create();
                operation.setup({input}, {output, output_index});
                operation.execute({input}, {output, output_index});
                return {output, output_index};
            }
        }

        // prod
        template <typename T>
        NdArrayPtr prod(NdArrayPtr input, vector<int64_t>& axes, bool keep_dims = false) 
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            Prod<T> operation(ctx, axes, keep_dims);
            auto output = NdArray::create();
            operation.setup({input}, {output});
            operation.execute({input}, {output});
            return {output};
        }

        // sort
        template <typename T>
        vector<NdArrayPtr> sort(NdArrayPtr input, int axis = 0, bool reverse = false, bool with_index = false, bool only_index = false) 
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            Sort<T> operation(ctx, {axis}, reverse, with_index, only_index);

            if (!with_index)
            {
                auto output = NdArray::create();
                operation.setup({input}, {output});
                operation.execute({input}, {output});
                return {output};
            }
            else
            {
                auto output = NdArray::create();
                auto output_index = NdArray::create();
                operation.setup({input}, {output, output_index});
                operation.execute({input}, {output, output_index});
                return {output, output_index};
            }
        }

        // cumsum
        template <typename T>
        NdArrayPtr cumsum(NdArrayPtr input, int axis = 0, bool exclusive = false, bool reverse = false) 
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            CumSum<T> operation(ctx, axis, exclusive, reverse);
            auto output = NdArray::create();
            operation.setup({input}, {output});
            operation.execute({input}, {output});
            return {output};           
        }

        // cumprod
        template <typename T>
        NdArrayPtr cumprod(NdArrayPtr input, int axis = 0, bool exclusive = false, bool reverse = false) 
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            CumProd<T> operation(ctx, axis, exclusive, reverse);
            auto output = NdArray::create();
            operation.setup({input}, {output});
            operation.execute({input}, {output});
            return {output};           
        }
    }
}