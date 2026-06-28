#include "../../include/repositories/SqliteUserRepository.hpp"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

void SqliteUserRepository::add(const User& user) {
    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password_hash) VALUES (:username, :password)");
    query.bindValue(":username", QString::fromStdString(user.getLogin()));
    query.bindValue(":password", QString::fromStdString(user.getPassword()));

    if (!query.exec()) {
        qDebug() << "Blad dodawania uzytkownika do SQL:" << query.lastError().text();
    }
}

std::optional<User> SqliteUserRepository::getByLogin(const std::string& username) const {
    QSqlQuery query;
    query.prepare("SELECT id, username, password_hash FROM users WHERE username = :username");
    query.bindValue(":username", QString::fromStdString(username));

    if (query.exec() && query.next()) {
        int id = query.value(0).toInt();
        std::string uName = query.value(1).toString().toStdString();
        std::string pHash = query.value(2).toString().toStdString();

        User user(uName, pHash);
        user.setId(id);
        return user;
    }
    return std::nullopt;
}

std::optional<User> SqliteUserRepository::getById(int id) const {
    QSqlQuery query;
    query.prepare("SELECT id, username, password_hash FROM users WHERE id = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        int uId = query.value(0).toInt();
        std::string uName = query.value(1).toString().toStdString();
        std::string pHash = query.value(2).toString().toStdString();

        User user(uName, pHash);
        user.setId(uId);
        return user;
    }
    return std::nullopt;
}