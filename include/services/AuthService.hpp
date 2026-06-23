#pragma once

#include <memory>
#include <optional>

#include "../repositories/IUserRepository.hpp"
#include "../validators/UserValidator.hpp"
#include "../models/Session.hpp"

class AuthService {
private:
    IUserRepository& userRepository;
    UserValidator&   userValidator;

public:
    AuthService(IUserRepository& repo, UserValidator& validator)
        : userRepository(repo), userValidator(validator) {}

    bool registerUser(const std::string& login, const std::string& password);
    std::optional<Session> loginUser(const std::string& login, const std::string& password);
};