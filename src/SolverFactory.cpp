
#include "SolverFactory.h"

template <class T>
Solver* SolverFactory::getOrCreate(const std::type_info& type_id,
                                   OpType op) throw(ComputeRes)
{
    return nullptr;
}
