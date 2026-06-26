#pragma once

#include "IUserRepository.hpp"
#include <QSqlDatabase>

class SqliteUserRepository : public IUserRepository {
public:
    SqliteUserRepository() = default;
    ~SqliteUserRepository() override = default;

    void add(const User& user) override;

    std::optional<User> getByLogin(const std::string& username) const override;

    std::optional<User> getById(int id) const override;
};