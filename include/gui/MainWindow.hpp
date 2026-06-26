#pragma once

#include <QMainWindow>
#include <QTableWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QPushButton>
#include "../models/Session.hpp"
#include "../services/TransactionService.hpp"
#include "../services/CategoryService.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    Session session;
    TransactionService& transactionService;
    CategoryService& categoryService;

    QTableWidget* transactionTable;
    QLineEdit* amountInput;
    QComboBox* categoryComboBox;
    QLineEdit* titleInput;
    QTextEdit* descriptionInput;
    QPushButton* addTransactionButton;
    QComboBox* transactionTypeComboBox;

    QPushButton* userMenuButton;
    QWidget*     userPopupMenu;
    void         setupUserMenu();

    void setupUi();
    void loadCategories();
    void loadTransactionTypes();
    void refreshTransactionHistory();

private slots:
    void handleAddTransaction();
    void toggleUserMenu();
    void handleLogout();

public:
    MainWindow(const Session& activeSession, 
               TransactionService& tService, 
               CategoryService& cService, 
               QWidget* parent = nullptr);

signals:
    void logoutRequested();
};