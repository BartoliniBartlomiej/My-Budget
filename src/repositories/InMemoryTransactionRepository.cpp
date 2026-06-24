#include "../../include/repositories/InMemoryTransactionRepository.hpp"

void InMemoryTransactionRepository::add(const Transaction& transaction) {
    Transaction newTransaction = transaction;
    newTransaction.setId(nextId++);
    transactions.push_back(newTransaction);
}

std::vector InMemoryTransactionRepository::getByUserId(int userId) const {
    std::vector<Transaction> userTransactions;

    for (const auto& transaction : transactions) {
        if (transaction.getUserId() == userId)
            userTransactions.push_back(transaction);
    }

    return userTransactions;
}

bool InMemoryTransactionRepository::removeById(int id) {
    for (auto it = transaction.begin(); it != transaction.end(); ++it) {
        if (it->getId() == id) {
            transactions.erase(it);
            return true;
        }
    }

    return false;
}