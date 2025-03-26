
#include "SolverFactory.h"

SolverFactory* SolverFactory::getInstance()
{
    static SolverFactory* instance = nullptr;
    if (!instance) instance = new SolverFactory;

    return instance;
}

template <class T>
Solver* SolverFactory::getOrCreate(const std::type_info& type_id, OpType op)
{
    return nullptr;
}
