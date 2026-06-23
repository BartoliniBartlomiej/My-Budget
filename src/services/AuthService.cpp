#include "../../include/services/AuthService.hpp"

bool AuthService::registerUser(const std::string& login, const std::string& password) {
    if (!userValidator.validateLogin(login) || !userValidator.validatePassword(password)) {
        return false;
    }

    if (userRepository.getByLogin(login).has_value()) {
        return false; // login occupied
    }

    User newUser(login, password);
    userRepository.add(newUser);
    
    return true;
}

std::optional<Session> AuthService::loginUser(const std::string& login, const std::string& password) {
    auto userOpt = userRepository.getByLogin(login);

    if (!userOpt.has_value()) {
        return std::nullopt;    // user doesnt exist
    }

    if (userOpt->getPassword() != password) {
        return std::nullopt;
    }

    return Session(userOpt->getId(), userOpt->getLogin());

}