
#include "ComputeRes.h"

ComputeRes* ComputeRes::getInstance() { return nullptr; }

int ComputeRes::initialize() { return 0; }

bool ComputeRes::isInitialized() { return false; }

cl_command_queue ComputeRes::getCommandQueue()
{
    if (!queues_cache.empty())
    {
        auto q = queues_cache.back();
        queues_cache.pop_back();

        return q;
    }
    return nullptr;
}
