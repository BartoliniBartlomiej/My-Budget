#pragma once

#include <memory>
#include <optional>
#include "../services/AuthService.hpp"
#include "../services/CategoryService.hpp"
#include "../services/TransactionService.hpp"
#include "../models/Session.hpp"

class CLIApp {
private:
    AuthService&        authService;
    CategoryService&    categoryService;
    TransactionService& transactionService;
    
    std::optional<Session> currentSession;
    bool running;

    void showMainMenu();
    void showUserMenu();
    
    void handleRegistration();
    void handleLogin();
    void handleAddTransaction();
    void handleShowHistory();

public:
    CLIApp(AuthService& auth, CategoryService& cat, TransactionService& trans)
        : authService(auth), categoryService(cat), transactionService(trans), running(true) {}

    void run();
};