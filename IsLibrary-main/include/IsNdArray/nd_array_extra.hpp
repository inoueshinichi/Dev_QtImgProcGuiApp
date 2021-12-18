#pragma once

#include <IsNdArray/nd_array.hpp>
#include <IsNdArray/global_context.hpp>

// Generation
#include <IsNdArray/function/rand.hpp>
#include <IsNdArray/function/randint.hpp>
#include <IsNdArray/function/randn.hpp>
#include <IsNdArray/function/arange.hpp>
#include <IsNdArray/function/constant.hpp>

// PointWise-1
#include <IsNdArray/function/abs.hpp>
#include <IsNdArray/function/exp.hpp>
#include <IsNdArray/function/sinc.hpp>
#include <IsNdArray/function/cos.hpp>
#include <IsNdArray/function/cosh.hpp>
#include <IsNdArray/function/acos.hpp>
#include <IsNdArray/function/acosh.hpp>
#include <IsNdArray/function/sin.hpp>
#include <IsNdArray/function/sinh.hpp>
#include <IsNdArray/function/asin.hpp>
#include <IsNdArray/function/asinh.hpp>
#include <IsNdArray/function/atan.hpp>
#include <IsNdArray/function/tan.hpp>
#include <IsNdArray/function/tanh.hpp>
#include <IsNdArray/function/atanh.hpp>
#include <IsNdArray/function/sqrt.hpp>
#include <IsNdArray/function/ceil.hpp>
#include <IsNdArray/function/floor.hpp>
#include <IsNdArray/function/round.hpp>
#include <IsNdArray/function/log.hpp>
#include <IsNdArray/function/log1p.hpp>
#include <IsNdArray/function/log2.hpp>
#include <IsNdArray/function/log10.hpp>
#include <IsNdArray/function/sigmoid.hpp>
#include <IsNdArray/function/sign.hpp>

// Pointwise-2
#include <IsNdArray/function/add_scalar.hpp>
#include <IsNdArray/function/pow_scalar.hpp>
#include <IsNdArray/function/mul_scalar.hpp>
#include <IsNdArray/function/r_div_scalar.hpp>
#include <IsNdArray/function/r_pow_scalar.hpp>
#include <IsNdArray/function/r_sub_scalar.hpp>
#include <IsNdArray/function/maximum_scalar.hpp>
#include <IsNdArray/function/minimum_scalar.hpp>

// Ope1
#include <IsNdArray/function/transpose.hpp>
#include <IsNdArray/function/broadcast.hpp>
#include <IsNdArray/function/reshape.hpp>
#include <IsNdArray/function/slice.hpp>
#include <IsNdArray/function/split.hpp>
#include <IsNdArray/function/concatenate.hpp>

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

        // constant
        template <typename T>
        NdArrayPtr constant(const Shape_t& shape, float val)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            Arange<T> operation(ctx, val, shape);
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

        // cos
        template <typename T>
        NdArrayPtr cos(NdArrayPtr input)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            Cos<T> operation(ctx);
            auto output = NdArray::create();
            output->cast_data_and_get_pointer<T>(ctx);
            operation.setup({input}, {output});
            operation.execute({input}, {output});
            return output;
        }

        // cosh
        template <typename T>
        NdArrayPtr cosh(NdArrayPtr input)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            Cosh<T> operation(ctx);
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

        // acosh
        template <typename T>
        NdArrayPtr acosh(NdArrayPtr input)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            ACosh<T> operation(ctx);
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

        // sinh
        template <typename T>
        NdArrayPtr sinh(NdArrayPtr input)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            Sinh<T> operation(ctx);
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

        // asinh
        template <typename T>
        NdArrayPtr asinh(NdArrayPtr input)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            ASinh<T> operation(ctx);
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

        // tanh
        template <typename T>
        NdArrayPtr tanh(NdArrayPtr input)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            Tanh<T> operation(ctx);
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

        // atanh
        template <typename T>
        NdArrayPtr atanh(NdArrayPtr input)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            ATanh<T> operation(ctx);
            auto output = NdArray::create();
            output->cast_data_and_get_pointer<T>(ctx);
            operation.setup({input}, {output});
            operation.execute({input}, {output});
            return output;
        }

        // sqrt
        template <typename T>
        NdArrayPtr sqrt(NdArrayPtr input)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            Sqrt<T> operation(ctx);
            auto output = NdArray::create();
            output->cast_data_and_get_pointer<T>(ctx);
            operation.setup({input}, {output});
            operation.execute({input}, {output});
            return output;
        }

        // ceil
        template <typename T>
        NdArrayPtr ceil(NdArrayPtr input)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            Ceil<T> operation(ctx);
            auto output = NdArray::create();
            output->cast_data_and_get_pointer<T>(ctx);
            operation.setup({input}, {output});
            operation.execute({input}, {output});
            return output;
        }

        // floor
        template <typename T>
        NdArrayPtr floor(NdArrayPtr input)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            Floor<T> operation(ctx);
            auto output = NdArray::create();
            output->cast_data_and_get_pointer<T>(ctx);
            operation.setup({input}, {output});
            operation.execute({input}, {output});
            return output;
        }

        // round
        template <typename T>
        NdArrayPtr round(NdArrayPtr input)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            Round<T> operation(ctx);
            auto output = NdArray::create();
            output->cast_data_and_get_pointer<T>(ctx);
            operation.setup({input}, {output});
            operation.execute({input}, {output});
            return output;
        }

        // log
        template <typename T>
        NdArrayPtr log(NdArrayPtr input)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            Log<T> operation(ctx);
            auto output = NdArray::create();
            output->cast_data_and_get_pointer<T>(ctx);
            operation.setup({input}, {output});
            operation.execute({input}, {output});
            return output;
        }

        // log1p
        template <typename T>
        NdArrayPtr log1p(NdArrayPtr input)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            Log1p<T> operation(ctx);
            auto output = NdArray::create();
            output->cast_data_and_get_pointer<T>(ctx);
            operation.setup({input}, {output});
            operation.execute({input}, {output});
            return output;
        }

        // log2
        template <typename T>
        NdArrayPtr log2(NdArrayPtr input)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            Log2<T> operation(ctx);
            auto output = NdArray::create();
            output->cast_data_and_get_pointer<T>(ctx);
            operation.setup({input}, {output});
            operation.execute({input}, {output});
            return output;
        }

        // log10
        template <typename T>
        NdArrayPtr log10(NdArrayPtr input)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            Log10<T> operation(ctx);
            auto output = NdArray::create();
            output->cast_data_and_get_pointer<T>(ctx);
            operation.setup({input}, {output});
            operation.execute({input}, {output});
            return output;
        }

        // sigmoid
        template <typename T>
        NdArrayPtr sigmoid(NdArrayPtr input)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            Sigmoid<T> operation(ctx);
            auto output = NdArray::create();
            output->cast_data_and_get_pointer<T>(ctx);
            operation.setup({input}, {output});
            operation.execute({input}, {output});
            return output;
        }

        // sign
        template <typename T>
        NdArrayPtr sign(NdArrayPtr input)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            Sign<T> operation(ctx);
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

        // maximum_scalar
        template <typename T>
        NdArrayPtr maximum_scalar(NdArrayPtr input, double val)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            MaximumScalar<T> operation(ctx, val);
            auto output = NdArray::create();
            output->cast_data_and_get_pointer<T>(ctx);
            operation.setup({input}, {output});
            operation.execute({input}, {output});
            return output;
        }

        // minimum_scalar
        template <typename T>
        NdArrayPtr minimum_scalar(NdArrayPtr input, double val)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            MinimumScalar<T> operation(ctx, val);
            auto output = NdArray::create();
            output->cast_data_and_get_pointer<T>(ctx);
            operation.setup({input}, {output});
            operation.execute({input}, {output});
            return output;
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


        // split
        template <typename T>
        vector<NdArrayPtr> split(NdArrayPtr input, int axis) 
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            Split<T> operation(ctx, axis);
            auto sh = input->shape();
            int num = sh.at(axis);
            vector<NdArrayPtr> outputs(num);
            for (int i = 0; i < num; ++i)
            {
                outputs[i] = NdArray::create();
            }
            operation.setup({input}, outputs);
            operation.execute({input}, outputs);
            return outputs;
        }


        // concatenate
        template <typename T>
        NdArrayPtr concatenate(vector<NdArrayPtr> inputs, int axis)
        {
            const auto &ctx = SingletonManager::get<GlobalContext>()->get_current_context();
            Concatenate<T> operation(ctx, axis);
            auto output = NdArray::create();
            operation.setup(inputs, {output});
            operation.execute(inputs, {output});
            return output;
        }

        // -------------------------------------------------------
        

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