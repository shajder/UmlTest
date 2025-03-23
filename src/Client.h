#ifndef _CLIENT_H
#define _CLIENT_H


#include <memory>
using namespace std;
#include <list>
using namespace std;

class Transaction;

// -fvisibility=hidden
#ifdef _WIN32
#ifdef BUILDING_CLIENT_DLL
#define CLIENT_API __declspec(dllexport)
#else
#define CLIENT_API __declspec(dllimport)
#endif
#else
#define CLIENT_API __attribute__((visibility("default")))
#endif

// Library interface class. Delivers interface to create and close compute
// transactions.
class CLIENT_API Client final {
public:
    shared_ptr<Transaction> createTransaction();

    int closeTransaction(shared_ptr<Transaction>& transaction);


private:
    list<shared_ptr<Transaction>> m_active_transactions;

    std::list<Transaction*> m_transaction_cache;

    std::shared_ptr<Transaction> m_transaction_active;
};
#endif
