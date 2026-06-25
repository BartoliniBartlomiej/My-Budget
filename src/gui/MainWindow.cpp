#include "../../include/gui/MainWindow.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QMessageBox>
#include <QHeaderView>
#include <QDate>

MainWindow::MainWindow(const Session& activeSession, 
                       TransactionService& tService, 
                       CategoryService& cService, 
                       QWidget* parent)
    : QMainWindow(parent), session(activeSession), 
      transactionService(tService), categoryService(cService) {
    
    setupUi();
    loadCategories();
    loadTransactionTypes();
    refreshTransactionHistory();

    connect(addTransactionButton, &QPushButton::clicked, this, &MainWindow::handleAddTransaction);
}

void MainWindow::setupUi() {
    setWindowTitle(QString("My Budget - Panel: %1").fromStdString(session.getUsername()));
    resize(800, 500);

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);

    // ================= LEFT PANEL =================
    QVBoxLayout* leftLayout = new QVBoxLayout();
    QLabel* formTitle = new QLabel("Add new transaction", this);
    formTitle->setStyleSheet("font-weight: bold; font-size: 14px;");
    leftLayout->addWidget(formTitle);

    QFormLayout* formLayout = new QFormLayout();
    
    amountInput = new QLineEdit(this);
    amountInput->setPlaceholderText("0.00");
    formLayout->addRow("Amount (PLN):", amountInput);

    categoryComboBox = new QComboBox(this);
    formLayout->addRow("Category:", categoryComboBox);

    transactionTypeComboBox = new QComboBox(this);
    formLayout->addRow("Transaction Type:", transactionTypeComboBox);

    titleInput = new QLineEdit(this);
    titleInput->setPlaceholderText("e.g., Shopping at the store");
    formLayout->addRow("Title:", titleInput);

    descriptionInput = new QLineEdit(this);
    descriptionInput->setPlaceholderText("(Optional)");
    formLayout->addRow("Description:", descriptionInput);

    leftLayout->addLayout(formLayout);

    addTransactionButton = new QPushButton("Add Transaction", this);
    leftLayout->addWidget(addTransactionButton);
    leftLayout->addStretch();

    // ================= RIGHT PANEL (TABLE) =================
    QVBoxLayout* rightLayout = new QVBoxLayout();
    QLabel* tableTitle = new QLabel("Transaction History", this);
    tableTitle->setStyleSheet("font-weight: bold; font-size: 14px;");
    rightLayout->addWidget(tableTitle);

    transactionTable = new QTableWidget(this);
    transactionTable->setColumnCount(4);
    transactionTable->setHorizontalHeaderLabels({"Date", "Amount", "Category", "Title"});
    transactionTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    transactionTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    rightLayout->addWidget(transactionTable);

    mainLayout->addLayout(leftLayout, 1);
    mainLayout->addLayout(rightLayout, 2);
}

void MainWindow::loadCategories() {
    categoryComboBox->clear();
    auto categories = categoryService.getAvailableCategories(session);
    for (const auto& cat : categories) {

        categoryComboBox->addItem(QString::fromStdString(cat.getName()), cat.getId());
    }
}

QString transactionTypeToString(TransactionType type) {
    switch (type) {
        case TransactionType::INCOME:
            return "Income";
        case TransactionType::EXPENSE:
            return "Expense";
        default:
            return "Unknown";
    }
}

void MainWindow::loadTransactionTypes() {
    transactionTypeComboBox->clear();

    for (TransactionType type : {TransactionType::INCOME, TransactionType::EXPENSE}) {
        transactionTypeComboBox->addItem(
            transactionTypeToString(type),
            static_cast<int>(type)
        );
    }
}

void MainWindow::refreshTransactionHistory() {
    auto history = transactionService.getTransactionHistory(session);
    transactionTable->setRowCount(0); 

    for (int i = 0; i < history.size(); ++i) {
        transactionTable->insertRow(i);
        
        auto catOpt = categoryService.getAvailableCategories(session);
        QString catName = "Unknown";
        for(const auto& c : catOpt) {
            if(c.getId() == history[i].getCategoryId()) {
                catName = QString::fromStdString(c.getName());
                break;
            }
        }

        transactionTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(history[i].getDate())));
        transactionTable->setItem(i, 1, new QTableWidgetItem(QString::number(history[i].getAmount(), 'f', 2) + " PLN"));
        transactionTable->setItem(i, 2, new QTableWidgetItem(catName));
        transactionTable->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(history[i].getTitle())));
    }
}

void MainWindow::handleAddTransaction() {
    double amount = amountInput->text().toDouble();
    int catId = categoryComboBox->currentData().toInt();
    TransactionType type = static_cast<TransactionType>(transactionTypeComboBox->currentData().toInt());
    std::string title = titleInput->text().toStdString();
    std::string description = descriptionInput->text().toStdString();
    std::string currentDate = QDate::currentDate().toString("yyyy-MM-dd").toStdString();
    
    if (transactionService.addTransaction(amount, catId, currentDate, title, RecurrenceInterval::NONE, session, type, description)) {
        refreshTransactionHistory();
        amountInput->clear();
        titleInput->clear();
        descriptionInput->clear();
    } else {
        QMessageBox::warning(this, "Error", "Failed to add transaction. Please check the amount.");
    }
}