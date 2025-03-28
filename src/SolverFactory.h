#ifndef _SOLVERFACTORY_H
#define _SOLVERFACTORY_H


#include "Solver.h"
#include "OpType.h"
#include "ComputeRes.h"

#include <map>

// Factory class of singleton type. Main task is to deliver interface for
// creation on Solver base on input arguments, data type and operation type.
class SolverFactory {
public:
    template <class T>
    Solver* getOrCreate(const std::type_info& type_id, OpType op);

    static SolverFactory* getInstance();


private:
    std::map<std::pair<size_t, OpType>, Solver*> solvers;
};
#endif
