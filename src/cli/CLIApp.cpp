#include "../../include/cli/CLIApp.hpp"
#include "../../include/cli/InputHelper.hpp"
#include <iostream>

void CLIApp::run() {
    categoryService.initializeDefaultCategories();

    std::cout << "=== MY BUDGET ===" << std::endl;
    
    while (running) {
        if (!currentSession.has_value() || !currentSession->isLoggedIn()) {
            showMainMenu();
        } else {
            showUserMenu();
        }
    }
}

void CLIApp::showMainMenu() {
    std::cout << "\n[MAIN MENU]\n";
    std::cout << "1. Login\n";
    std::cout << "2. Register\n";
    std::cout << "3. Exit\n";
    
    int choice = InputHelper::readInt("Choose option: ");
    
    switch (choice) {
        case 1: handleLogin(); break;
        case 2: handleRegistration(); break;
        case 3: running = false; break;
        default: std::cout << "Invalid option.\n";
    }
}

void CLIApp::showUserMenu() {
    std::cout << "\n[USER PANEL: " << currentSession->getUsername() << "]\n";
    std::cout << "1. Add transaction\n";
    std::cout << "2. Show expense history\n";
    std::cout << "3. Logout\n";
    
    int choice = InputHelper::readInt("Choose option: ");
    
    switch (choice) {
        case 1: handleAddTransaction(); break;
        case 2: handleShowHistory(); break;
        case 3: 
            currentSession->logout();
            currentSession = std::nullopt;
            std::cout << "Logged out successfully.\n";
            break;
        default: std::cout << "Invalid option!\n";
    }
}

void CLIApp::handleRegistration() {
    std::cout << "\n--- REGISTRATION ---\n";
    std::string login = InputHelper::readString("Enter login (min. 3 characters): ");
    std::string password = InputHelper::readString("Enter password (min. 6 characters): ");
    
    if (authService.registerUser(login, password)) {
        std::cout << "Account created successfully! You can now log in.\n";
    } else {
        std::cout << "Registration error! Check requirements or try a different login.\n";
    }
}

void CLIApp::handleLogin() {
    std::cout << "\n--- LOGIN ---\n";
    std::string login = InputHelper::readString("Login: ");
    std::string password = InputHelper::readString("Password: ");
    
    auto sessionOpt = authService.loginUser(login, password);
    if (sessionOpt.has_value()) {
        currentSession = sessionOpt;
        std::cout << "Login successful! Welcome, " << currentSession->getUsername() << ".\n";
    } else {
        std::cout << "Error: Incorrect login or password.\n";
    }
}

void CLIApp::handleAddTransaction() {
    std::cout << "\n--- ADD TRANSACTION ---\n";
    
    std::cout << "Available categories:\n";
    auto categories = categoryService.getAvailableCategories(*currentSession);
    for (const auto& cat : categories) {
        std::cout << " ID: " << cat.getId() << " | " << cat.getName() << "\n";
    }
    
    double amount = InputHelper::readDouble("Enter amount (e.g. 45.50): ");
    int catId = InputHelper::readInt("Enter category ID: ");
    std::string description = InputHelper::readString("Transaction description: ");
    std::string date = InputHelper::readString("Date (YYYY-MM-DD): ");
    
    if (transactionService.addTransaction(amount, catId, date, description, RecurrenceInterval::NONE, *currentSession)) {
        std::cout << "Transaction added successfully!\n";
    } else {
        std::cout << "Error: Could not add transaction (check amount or category ID).\n";
    }
}

void CLIApp::handleShowHistory() {
    std::cout << "\n--- TRANSACTION HISTORY ---\n";
    auto history = transactionService.getTransactionHistory(*currentSession);
    
    if (history.empty()) {
        std::cout << "No transactions found.\n";
        return;
    }
    
    for (const auto& t : history) {
        std::cout << "[" << t.getDate() << "] " << t.getAmount() << " PLN - " << t.getDescription() << "\n";
    }
}