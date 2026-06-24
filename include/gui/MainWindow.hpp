#pragma once

#include <QMainWindow>
#include <QTableWidget>
#include <QLineEdit>
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
    QPushButton* addTransactionButton;
    QComboBox* transactionTypeComboBox;

    void setupUi();
    void loadCategories();
    void loadTransactionTypes();
    void refreshTransactionHistory();

private slots:
    void handleAddTransaction();

public:
    MainWindow(const Session& activeSession, 
               TransactionService& tService, 
               CategoryService& cService, 
               QWidget* parent = nullptr);
};