#ifndef _SOLVERIMPL_H
#define _SOLVERIMPL_H


#include "Solver.h"
#include "OpType.h"
#include <string>
using namespace std;
#include "ComputeRes.h"

template<class T>
class SolverImpl : public Solver {
  public:
    int createKernel(OpType op_type);


  private:
    cl_program program;

    cl_kernel kernel;

    string kernel_src;

};
#endif
