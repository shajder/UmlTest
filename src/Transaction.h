#ifndef _TRANSACTION_H
#define _TRANSACTION_H


#include "TransactionState.h"
#include "OpType.h"

class Client;
class Solver;

#include <vector>
#include <mutex>

//This class represent slot for concurency computations. Life cycle of each session includes activation of the object, launching computations by providing a single barch of data, collecting the data and closing the transaction.
class Transaction final {
friend class Client;
friend class Solver;
  private:
    TransactionState m_state;


  public:
    TransactionState state();

    template<class T>
    int run(const T* & src, unsigned int src_size, OpType op_type);


  private:
    std::vector<char> m_dst;


  public:
    template <typename T> int result(T* & dst, unsigned int & dst_size);


  private:
    int close();

    Client * m_client;

    Solver * m_solver;


  public:
    void onNotifyComputeDone();


  private:
    std::mutex m_state_mutex;

};
#endif
