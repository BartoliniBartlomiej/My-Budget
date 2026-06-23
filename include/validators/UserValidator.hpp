#pragma once

#include <string>

class UserValidator {
public:
    bool validateLogin(const std::string& loginToValidation);
    bool validatePassword(const std::string& passwordToValidation);
};