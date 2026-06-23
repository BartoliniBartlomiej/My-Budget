#pragma once

#include <memory>
#include <optional>
#include <string>
#include "../models/User.hpp"

class IUserRepository {
public:
    virtual ~IUserRepository() = default;

    virtual void add(const User& user) = 0;

    virtual std::optional<User> getById(int id) const = 0;

    virtual std::optional<User> getByLogin(const std::string& login) const = 0;
};