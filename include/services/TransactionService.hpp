#pragma once

#include <vector>
#include <string>
#include "../repositories/ITransactionRepository.hpp"
#include "../repositories/ICategoryRepository.hpp"
#include "../models/Session.hpp"
#include "../enums/Enums.hpp"

class TransactionService {
private:
    ITransactionRepository& transactionRepository;
    ICategoryRepository& categoryRepository;

public:
    TransactionService(ITransactionRepository& tRepo, ICategoryRepository& cRepo) 
        : transactionRepository(tRepo), categoryRepository(cRepo) {}
        
    bool addTransaction(double amount, int categoryId, const std::string& date, const std::string& description, RecurrenceInterval recurrence, const Session& session);
    bool addTransaction(double amount, int categoryId, const std::string& date, const std::string& title, RecurrenceInterval recurrence, const Session& session, const TransactionType type, const std::string& description = "");

    std::vector<Transaction> getTransactionHistory(const Session& session) const;
};