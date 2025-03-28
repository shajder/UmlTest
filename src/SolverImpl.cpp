
#include "SolverImpl.h"
#include <vector>
#include <stdexcept>
#include <iostream>
#include <sstream>

template <class T> SolverImpl<T>::SolverImpl(OpType& ot)
{
    std::vector<char> program_source(4096);

    std::string type_name;
    if constexpr (std::is_same<T, cl_int>::value)
    {
        type_name = "int";
    }
    else if constexpr (std::is_same<T, cl_float>::value)
    {
        type_name = "float";
    }
    else
    {
        throw std::runtime_error("Unsupported data type");
    }

    switch (ot)
    {
        case OP_SIN:
            if constexpr (!std::is_floating_point<T>::value)
            {
                throw std::runtime_error(
                    "sin operation not supported with integer data");
            }

            kernel_src =
                R"(__kernel void compute(__global float *src, __global float *dst)
            {
                size_t id = get_global_id(0);
                dst[id] = sin(src[id]);
            })";

            break;
        case OP_MAX:
            const char* pattern =
                R"(__kernel void compute(__global %s *src, __global %s *dst)
            {
                size_t id = get_global_id(0);
                dst[id] = %s(src[id*2], src[id*2+1]);
            })";

            std::string op_name = "fmax";
            if constexpr (!std::is_floating_point<T>::value) op_name = "max";

            sprintf(program_source.data(), pattern, type_name.c_str(),
                    type_name.c_str(), op_name.c_str());

            kernel_src = program_source.data();
            break;
        case OP_FMA:
            if constexpr (!std::is_floating_point<T>::value)
            {
                throw std::runtime_error(
                    "fma operation not supported with integer data");
            }

            kernel_src =
                R"(__kernel void compute(__global float *src, __global float *dst)
            {
                size_t id = get_global_id(0);
                dst[id] = fma(src[id*3], src[id*3+1], src[id*3+2]);
            })";
            break;
    }
}


template <class T> int SolverImpl<T>::createKernel(OpType op_type)
{
    auto inst = ComputeRes::getInstance();

    cl_int err = CL_SUCCESS;
    const char* src = kernel_src.c_str();
    program = clCreateProgramWithSource(inst->context, 1, (const char**)&src,
                                        nullptr, &err);
    if (err != CL_SUCCESS)
    {
        std::cout << "Error: Unable to create program" << std::endl;
        return -1;
    }

    err = clBuildProgram(program, 1, &inst->device, NULL, NULL, NULL);
    if (err != CL_SUCCESS)
    {
        char buffer[2048];
        size_t length;
        clGetProgramBuildInfo(program, inst->device, CL_PROGRAM_BUILD_LOG,
                              sizeof(buffer), buffer, &length);
        std::stringstream sstr;
        sstr << "Error: Unable to build program" << std::endl
             << buffer << std::endl;

        std::cout << sstr.str().c_str();
        return -1;
    }

    kernel = clCreateKernel(program, "compute", &err);
    if (err != CL_SUCCESS)
    {
        std::cout << "Error: Unable to create kernel" << std::endl;
        return -1;
    }
}

template <class T>
int SolverImpl<T>::compute(const void*& src, int src_size, const void*& dst,
                           int dst_size, const Transaction*& cb)
{
    cl_int err;

    auto inst = ComputeRes::getInstance();

    cl_mem inputBuffer =
        clCreateBuffer(inst->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                       src_size, (void*)src, &err);
    if (err != CL_SUCCESS)
    {
        fprintf(stderr, "Failed to create input buffer.\n");
        return -1;
    }

    cl_mem outputBuffer =
        clCreateBuffer(inst->context, CL_MEM_WRITE_ONLY, dst_size, NULL, &err);
    if (err != CL_SUCCESS)
    {
        fprintf(stderr, "Failed to create output buffer.\n");
        clReleaseMemObject(inputBuffer);
        return -1;
    }

    err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer);
    if (err != CL_SUCCESS)
    {
        fprintf(stderr, "Failed to set kernel argument for input buffer.\n");
        clReleaseMemObject(inputBuffer);
        clReleaseMemObject(outputBuffer);
        return -1;
    }

    err = clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    if (err != CL_SUCCESS)
    {
        fprintf(stderr, "Failed to set kernel argument for output buffer.\n");
        clReleaseMemObject(inputBuffer);
        clReleaseMemObject(outputBuffer);
        return -1;
    }

    size_t globalWorkSize = src_size / sizeof(T);
    err = clEnqueueNDRangeKernel(inst->queue, kernel, 1, NULL, &globalWorkSize,
                                 NULL, 0, NULL, NULL);
    if (err != CL_SUCCESS)
    {
        fprintf(stderr, "Failed to enqueue kernel.\n");
        clReleaseMemObject(inputBuffer);
        clReleaseMemObject(outputBuffer);
        return -1;
    }

    err = clEnqueueReadBuffer(inst->queue, outputBuffer, CL_TRUE, 0, dst_size,
                              dst, 0, NULL, NULL);
    if (err != CL_SUCCESS)
    {
        fprintf(stderr, "Failed to read from output buffer.\n");
    }

    clReleaseMemObject(inputBuffer);
    clReleaseMemObject(outputBuffer);

    return 0;
}
