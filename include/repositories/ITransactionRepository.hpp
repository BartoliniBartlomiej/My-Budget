#pragma once

#include <vector>
#include <optional>

#include "../models/Transaction.hpp"

class ITransactionRepository {
public:
    virtual ~ITransactionRepository() = default;

    virtual void add(const Transaction& transaction, int userId) = 0;
    virtual std::vector<Transaction> getByUserId(int userId) const = 0;
    virtual bool removeById(int id) = 0;
};