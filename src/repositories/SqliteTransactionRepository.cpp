#include "../../include/repositories/SqliteTransactionRepository.hpp"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

void SqliteTransactionRepository::add(const Transaction& transaction, int userId) {
    QSqlQuery query;
    query.prepare(
        "INSERT INTO transactions (amount, category_id, date, description, user_id) "
        "VALUES (:amount, :category_id, :date, :description, :user_id)"
    );
    query.bindValue(":amount", transaction.getAmount());
    query.bindValue(":category_id", transaction.getCategoryId());
    query.bindValue(":date", QString::fromStdString(transaction.getDate()));

    query.bindValue(":description", QString::fromStdString(transaction.getDescription()));
    query.bindValue(":user_id", userId);

    if (!query.exec()) {
        qDebug() << "Error while adding transaction to SQL:" << query.lastError().text();
    }
}

std::vector<Transaction> SqliteTransactionRepository::getByUserId(int userId) const {
    std::vector<Transaction> result;
    QSqlQuery query;

    query.prepare(
        "SELECT id, amount, category_id, date, description "
        "FROM transactions WHERE user_id = :user_id ORDER BY date DESC"
    );
    query.bindValue(":user_id", userId);

    if (query.exec()) {
        while (query.next()) {
            double amount = query.value(1).toDouble();
            int categoryId = query.value(2).toInt();
            std::string date = query.value(3).toString().toStdString();
            std::string description = query.value(4).toString().toStdString();

            Transaction t(
                amount,                          // _amount
                categoryId,                      // _categoryId
                CategoryType::OTHER,             // _categoryType
                date,                            // _date
                description,                     // _title (używamy opisu jako tytułu)
                userId,                          // _userId
                RecurrenceInterval::NONE,        // _recurrence
                TransactionType::EXPENSE,        // _type (zakładamy domyślnie wydatek)
                description                      // _description
            );
            
            t.setId(query.value(0).toInt());
            result.push_back(t);
        }
    } else {
        qDebug() << "Error while getting transaction from SQL:" << query.lastError().text();
    }
    return result;
}

std::string SqliteTransactionRepository::intervalToString(RecurrenceInterval interval) const {
    if (interval == RecurrenceInterval::WEEKLY)  return "WEEKLY";
    if (interval == RecurrenceInterval::MONTHLY) return "MONTHLY";
    return "NONE";
}

RecurrenceInterval SqliteTransactionRepository::stringToInterval(const std::string& str) const {
    if (str == "WEEKLY")  return RecurrenceInterval::WEEKLY;
    if (str == "MONTHLY") return RecurrenceInterval::MONTHLY;
    return RecurrenceInterval::NONE;
}

bool SqliteTransactionRepository::removeById(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM transactions WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Error while deleting transaction from SQL based on id" << id << ":" << query.lastError().text();
        return false;
    }

    return query.numRowsAffected() > 0;
}