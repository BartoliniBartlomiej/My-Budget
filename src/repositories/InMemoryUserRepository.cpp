#include "../../include/repositories/InMemoryUserRepository.hpp"

void InMemoryUserRepository::add(const User& user) {
    User newUser = user;
    newUser.setId(nextId++);
    users.push_back(newUser);
}

std::optional<User> InMemoryUserRepository::getById(int id) const {
    for (const auto& user : users) {
        if (user.getId() == id) {
            return user;
        }
    }
    return std::nullopt;
}

std::optional<User> InMemoryUserRepository::getByLogin(const std::string& login) const {
    for (const auto& user : users) {
        if (user.getLogin() == login) {
            return user;
        }
    }
    return std::nullopt;
}