#ifndef _TRANSACTION_H
#define _TRANSACTION_H


#include "TransactionState.h"
#include "SolverFactory.h"
#include "OpType.h"

#ifdef _WIN32
#ifdef BUILDING_CLIENT_DLL
#define CLIENT_API __declspec(dllexport)
#else
#define CLIENT_API __declspec(dllimport)
#endif
#else
#define CLIENT_API __attribute__((visibility("default")))
#endif

class Client;
class Solver;

#include <vector>
#include <mutex>

// This class represent slot for concurency computations. Life cycle of each
// session includes activation of the object, launching computations by
// providing a single barch of data, collecting the data and closing the
// transaction.
class CLIENT_API Transaction final {
    friend class Client;
    friend class Solver;

private:
    TransactionState m_state;


public:
    TransactionState state();

    template <class T>
    int run(const T*& src, unsigned int src_size, OpType op_type);

    template <class T> int setup(OpType ot, unsigned int src_size);

    int cleanup();

private:
    std::vector<char> m_dst;


public:
    template <typename T> int result(T*& dst, unsigned int& dst_size);


private:
    int close();

    Client* m_client;

    Solver* m_solver;


public:
    void onNotifyComputeDone();


private:
    std::mutex m_state_mutex;
};
#endif
