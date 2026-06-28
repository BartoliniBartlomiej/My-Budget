#pragma once

#include "ITransactionRepository.hpp"
#include "../models/Session.hpp"
#include <QSqlDatabase>

class SqliteTransactionRepository : public ITransactionRepository {
private:
    std::string intervalToString(RecurrenceInterval interval) const;
    RecurrenceInterval stringToInterval(const std::string& str) const;

public:
    SqliteTransactionRepository() = default;
    ~SqliteTransactionRepository() override = default;

    void add(const Transaction& transaction, int userId) override;
    std::vector<Transaction> getByUserId(int userId) const override;
    bool removeById(int id) override;
};