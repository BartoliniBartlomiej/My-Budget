#include "../../include/repositories/InMemoryTransactionRepository.hpp"

void InMemoryTransactionRepository::add(const Transaction& transaction, int userId) {
    Transaction newTransaction = transaction;
    newTransaction.setId(nextId++);
    transactions.push_back(newTransaction);
}

std::vector<Transaction> InMemoryTransactionRepository::getByUserId(int userId) const {
    std::vector<Transaction> userTransactions;

    for (const auto& transaction : transactions) {
        if (transaction.getUserId() == userId)
            userTransactions.push_back(transaction);
    }

    return userTransactions;
}

bool InMemoryTransactionRepository::removeById(int id) {
    for (auto it = transactions.begin(); it != transactions.end(); ++it) {
        if (it->getId() == id) {
            transactions.erase(it);
            return true;
        }
    }

    return false;
}