
#include "Transaction.h"
#include "Client.h"
#include "Solver.h"

TransactionState Transaction::state() { return m_state; }

template <class T> int Transaction::setup(OpType ot, unsigned int src_size) 
{
    if (m_state != TS_IDLE) return -1;

    if (!m_solver)
    {
        auto inst = SolverFactory::getInstance();

        if (!inst) return -1;
        m_solver = inst->getOrCreate<T>(ot);
    }
    int div = 1;
    switch (ot)
    {
        default:
        case OP_SIN: div = 1; break;
        case OP_MAX: div = 2; break;
        case OP_FMA: div = 3; break;
    }
    m_dst.resize(sizeof(T) * src_size / div);

    return 0; 
}

int Transaction::cleanup() {
    m_dst.assign(m_dst.size(), 0);
    m_dst.clear();
    m_solver = nullptr;
    return 0; 
}

template <class T>
int Transaction::run(const T*& src, unsigned int src_size, OpType op_type)
{
    if (!m_solver || m_state != TS_IDLE) return -1;

    m_solver->compute<T>(src, src_size, m_dst.data(), m_dist.size() / sizeof(T),
                         this);

    return 0;
}

template <typename T> int Transaction::result(T*& dst, unsigned int& dst_size)
{
    if (m_state != TS_DONE) return -2;
    dst = m_dst.data();
    dst_size = m_dst.size()/sizeof(T);
    return 0;
}

int Transaction::close() {
    m_state = TS_IDLE;
    return 0; 
}

void Transaction::onNotifyComputeDone() 
{
    m_state = TS_DONE;
}
