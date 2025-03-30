#ifndef _COMPUTERES_H
#define _COMPUTERES_H


#include <CL/cl.h>
#include <mutex>
#include <list>

// Wrapper class for main OpenCL objects. Access for the objects of the class
// must be performed throuh thread-safe interface.
class ComputeRes {
public:
    cl_platform_id platform;

    cl_device_id device;

    cl_context context;


private:
    std::list<cl_command_queue> queues_active;


public:
    static ComputeRes* getInstance();


private:
    std::mutex res_mutex;

    std::list<cl_command_queue> queues_cache;


public:
    int initialize();

    cl_command_queue getCommandQueue();


private:
    bool initialized = false;


public:
    bool isInitialized();
};
#endif
