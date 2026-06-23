#include "../../include/validators/UserValidator.hpp"

bool UserValidator::validateLogin(const std::string& loginToValidation) {
    if (loginToValidation.empty() || loginToValidation.length() < 3) {
        return false;
    }
    return true;
}

bool UserValidator::validatePassword(const std::string& passwordToValidation) {
    if (passwordToValidation.empty() || passwordToValidation.length() < 6) {
        return false;
    }
    return true;
}