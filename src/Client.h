#ifndef _CLIENT_H
#define _CLIENT_H

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


#include <string>
using namespace std;
#include <list>
using namespace std;

class Transaction;

//Library interface class. Delivers interface to create and close compute transactions.
class CLIENT_API Client final {
  public:
    int createTransaction(const void* & src, unsigned int src_size, void* & dst, unsigned int dst_size, string op_name);

    int closeTransaction(Transaction & transaction);


  private:
    list<Transaction *> m_active_transactions;

    std::list<Transaction*> m_transaction_cache;

};
#endif
