#ifndef _SOLVER_H
#define _SOLVER_H


#include <list>
#include <memory>

using namespace std;
#include "ComputeRes.h"

class Transaction;

// Template class to deliver computation implementation for specific data and
// operation type.
class Solver {
public:
    virtual int compute(const void*& src, int src_size, const void*& dst,
                        int dst_size, const Transaction*& cb) = 0;


private:
    list<std::shared_ptr<Transaction>> m_active_transactions;
};
#endif
