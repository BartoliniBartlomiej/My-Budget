#pragma once

#include <string>

class Session {
    int         userId;
    std::string username;
    bool        loggedIn;

public:
    Session(int _userId, std::string _username) : userId(_userId), username(_username) {}

    int         getUserId()   const {   return userId;     }
    std::string getUsername() const {   return username;   }
    
};