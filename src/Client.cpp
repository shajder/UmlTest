
#include "Client.h"
#include "Transaction.h"

shared_ptr<Transaction> Client::createTransaction()
{
    return std::shared_ptr<Transaction>();
}

int Client::closeTransaction(shared_ptr<Transaction>& transaction) { return 0; }
