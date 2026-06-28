#include "../../include/services/TransactionService.hpp"

bool TransactionService::addTransaction(double amount, int categoryId, const std::string& date, 
                                        const std::string& description, RecurrenceInterval recurrence, 
                                        const Session& session) {
    if (!session.isLoggedIn()) {
        return false;
    }
    if (amount <= 0.0) {
        return false;
    }

    auto categoryOpt = categoryRepository.getById(categoryId);
    if (!categoryOpt.has_value()) {
        return false;
    }

    if (categoryOpt->getUserId() != 0 && categoryOpt->getUserId() != session.getUserId()) {
        return false;
    }

    Transaction transaction(amount, categoryId, date, description, session.getUserId(), recurrence);
    transactionRepository.add(transaction, session.getUserId());
    return true;
}

bool TransactionService::addTransaction(double amount, int categoryId, const std::string& date, 
                                        const std::string& title, RecurrenceInterval recurrence, 
                                        const Session& session, const TransactionType type, const std::string& description) {
    if (!session.isLoggedIn()) {
        return false;
    }
    if (amount <= 0.0) {
        return false;
    }

    auto categoryOpt = categoryRepository.getById(categoryId);
    if (!categoryOpt.has_value()) {
        return false;
    }

    if (categoryOpt->getUserId() != 0 && categoryOpt->getUserId() != session.getUserId()) {
        return false;
    }

    Transaction transaction(amount, categoryId, categoryOpt->getType(), date, title, session.getUserId(), recurrence, type, description);
    transactionRepository.add(transaction, session.getUserId());
    return true;
}

std::vector<Transaction> TransactionService::getTransactionHistory(const Session& session) const {
    if (!session.isLoggedIn()) {
        return {};
    }
    return transactionRepository.getByUserId(session.getUserId());
}