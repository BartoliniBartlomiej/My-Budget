#pragma once

#include <string>

class Session {
private:
    int         userId;
    std::string username;
    bool        loggedIn;

public:
    Session(int _userId, std::string _username) 
        : userId(_userId), username(_username), loggedIn(true) {}

    int         getUserId()   const {   return userId;     }
    std::string getUsername() const {   return username;   }
    bool        isLoggedIn()  const {   return loggedIn;   }
    
    void logout() { loggedIn = false; }
};