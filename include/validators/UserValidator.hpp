#pragma once

#include <string>

class UserValidator {
public:
    bool validateLogin(std::string loginToValidation);
    bool validatePassword(std::string passwordToValidation);
};