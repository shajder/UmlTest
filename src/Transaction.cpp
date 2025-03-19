
#include "Transaction.h"
#include "Client.h"
#include "Solver.h"

TransactionState Transaction::state() {
  return (TransactionState)0;
}

template<class T>
int Transaction::run(const T* & src, unsigned int src_size, OpType op_type) {
  return 0;
}

template <typename T> int Transaction::result(T* & dst, unsigned int & dst_size) {
  return 0;
}

int Transaction::close() {
  return 0;
}

void Transaction::onNotifyComputeDone() {
}

