
#include "Client.h"
#include "Transaction.h"

shared_ptr<Transaction> Client::createTransaction()
{
    std::shared_ptr<Transaction> transaction = nullptr;
    if (!m_transaction_cache.empty())
    {
        transaction = m_transaction_cache.back();
        m_transaction_cache.pop_back();
    }
    else
    {
        transaction = std::make_shared<Transaction>();
    }

    m_active_transactions.push_back(transaction);
    return transaction;
}

int Client::closeTransaction(shared_ptr<Transaction>& transaction)
{
    if (transaction && transaction->state() == TS_DONE)
    {
        transaction->close();
        return 0;
    }

    return -1;
}
