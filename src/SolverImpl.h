#ifndef _SOLVERIMPL_H
#define _SOLVERIMPL_H


#include "Solver.h"
#include "OpType.h"
#include <string>
using namespace std;
#include "ComputeRes.h"

template <class T> class SolverImpl : public Solver {
public:
    SolverImpl<T>(OpType&);
    int createKernel(OpType op_type);
    int compute(const void*& src, int src_size, const void*& dst, int dst_size,
                const Transaction*& cb) override;


private:
    cl_program program;

    cl_kernel kernel;

    string kernel_src;
};
#endif
