#pragma once

#include "ITransactionRepository.hpp"

class InMemoryTransactionRepository : public ITransactionRepository {
private:
    std::vector<Transaction> transactions;
    int nextId = 1;

public:
    void add(const Transaction& transaction) override;
    std::vector<Transaction> getByUserId(int userId) const override;
    bool removeById(int id) override;
};