
#include "SolverFactory.h"
#include "SolverImpl.h"

SolverFactory* SolverFactory::getInstance()
{
    static SolverFactory* instance = nullptr;
    if (!instance) instance = new SolverFactory;

    return instance;
}

template <class T>
Solver* SolverFactory::getOrCreate(const std::type_info& type_id, OpType op)
{
    if (solvers.find(std::make_pair(type_id.hash_code(), op)) == solvers.end())
    {
        solvers[std::make_pair(type_id.hash_code(), op)] =
            new SolverImpl<T>(op);
    }
    return nullptr;
}
