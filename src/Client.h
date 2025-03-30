#ifndef _CLIENT_H
#define _CLIENT_H

#include <memory>
#include <list>
using namespace std;

class Transaction;

#ifdef _WIN32
#ifdef BUILDING_CLIENT_DLL
#define CLIENT_API __declspec(dllexport)
#else
#define CLIENT_API __declspec(dllimport)
#endif
#else
// -fvisibility=hidden
#define CLIENT_API __attribute__((visibility("default")))
#endif

// Library interface class. Delivers interface to create and close compute
// transactions.
class CLIENT_API Client final {
public:
    Client();
    ~Client();
    shared_ptr<Transaction> createTransaction();

    int closeTransaction(shared_ptr<Transaction>& transaction);

private:
    std::list<shared_ptr<Transaction>> m_active_transactions;

    std::list<shared_ptr<Transaction>> m_transaction_cache;

    std::shared_ptr<Transaction> m_transaction_active;
};
#endif
