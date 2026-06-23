#pragma once

#include "IUserRepository.hpp"

#include <vector>
#include <optional>

class InMemoryUserRepository : public IUserRepository {
private:
    std::vector<User> users;
    int nextId = 1;

public:
    void add(const User& user) override;
    std::optional<User> getById(int id) const override;
    std::optional<User> getByLogin(const std::string& login) const override;
};