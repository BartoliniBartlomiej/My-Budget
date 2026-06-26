#include "../../include/repositories/SqliteCategoryRepository.hpp"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

void SqliteCategoryRepository::add(const Category& category) {
    QSqlQuery query;
    query.prepare("INSERT INTO categories (name, type, user_id) VALUES (:name, :type, :user_id)");
    query.bindValue(":name", QString::fromStdString(category.getName()));
    query.bindValue(":type", QString::fromStdString(typeToString(category.getType())));
    query.bindValue(":user_id", category.getUserId());

    if (!query.exec()) {
        qDebug() << "Error while adding Category to SQL:" << query.lastError().text();
    }
}

std::optional<Category> SqliteCategoryRepository::getById(int id) const {
    QSqlQuery query;
    query.prepare("SELECT id, name, type, user_id FROM categories WHERE id = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        Category cat(
            query.value(1).toString().toStdString(),
            stringToType(query.value(2).toString().toStdString()),
            query.value(3).toInt()
        );
        cat.setId(query.value(0).toInt());
        return cat;
    }
    return std::nullopt;
}

std::vector<Category> SqliteCategoryRepository::getByUserId(int userId) const {
    std::vector<Category> result;
    QSqlQuery query;
    // Pobieramy kategorie globalne (user_id = 0) LUB przypisane do konkretnego użytkownika
    query.prepare("SELECT id, name, type, user_id FROM categories WHERE user_id = 0 OR user_id = :user_id");
    query.bindValue(":user_id", userId);

    if (query.exec()) {
        while (query.next()) {
            Category cat(
                query.value(1).toString().toStdString(),
                stringToType(query.value(2).toString().toStdString()),
                query.value(3).toInt()
            );
            cat.setId(query.value(0).toInt());
            result.push_back(cat);
        }
    }
    return result;
}

std::string SqliteCategoryRepository::typeToString(CategoryType type) const {
    switch (type) {
        case CategoryType::FOOD:          return "FOOD";
        case CategoryType::HOUSING:       return "HOUSING";
        case CategoryType::TRANSPORT:     return "TRANSPORT";
        case CategoryType::ENTERTAINMENT: return "ENTERTAINMENT";
        case CategoryType::SALARY:        return "SALARY";
        default:                          return "OTHER";
    }
}

CategoryType SqliteCategoryRepository::stringToType(const std::string& str) const {
    if (str == "FOOD")          return CategoryType::FOOD;
    if (str == "HOUSING")       return CategoryType::HOUSING;
    if (str == "TRANSPORT")     return CategoryType::TRANSPORT;
    if (str == "ENTERTAINMENT") return CategoryType::ENTERTAINMENT;
    if (str == "SALARY")        return CategoryType::SALARY;
    return CategoryType::OTHER;
}