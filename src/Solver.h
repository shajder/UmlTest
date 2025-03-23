#ifndef _SOLVER_H
#define _SOLVER_H


#include <list>
using namespace std;
#include "ComputeRes.h"

class Transaction;

// Template class to deliver computation implementation for specific data and
// operation type.
class Solver {
public:
    template <class T>
    int compute(const T*& src, int src_size, const T*& dst, int dst_size,
                const Transaction*& cb);


private:
    list<Transaction*> m_transactions;
};
#endif
