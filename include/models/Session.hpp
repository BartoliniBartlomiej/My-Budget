#pragma once

#include <string>
#include "enums/Enums.hpp"

class Session {
private:
    int         userId;
    std::string username;
    bool        loggedIn;
    Currency    currency;

public:
    Session(int _userId, std::string _username) 
        : userId(_userId), username(_username), loggedIn(true), currency(Currency::USD) {}

    int         getUserId()   const {   return userId;     }
    std::string getUsername() const {   return username;   }
    bool        isLoggedIn()  const {   return loggedIn;   }
    Currency    getCurrency() const {   return currency;   }

    void logout() { loggedIn = false; }
    void setCurrency(Currency _currency) { currency = _currency; }

   std::string getCurrencyString() const {
        switch (currency) {
            case Currency::PLN: return "PLN";
            case Currency::USD: return "USD";
            case Currency::EUR: return "EUR";
            case Currency::GBP: return "GBP";
            default:            return "Unknown";
        }
    }
};