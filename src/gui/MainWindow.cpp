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
    setWindowTitle(QString("Spending Manager - Panel: %1").fromStdString(session.getUsername()));
    resize(800, 500);

    // Główny widget i horyzontalny layout dzielący okno na Lewo/Prawo
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);

    // ================= LEWY PANEL: FORMULARZ =================
    QVBoxLayout* leftLayout = new QVBoxLayout();
    QLabel* formTitle = new QLabel("Dodaj nową transakcję", this);
    formTitle->setStyleSheet("font-weight: bold; font-size: 14px;");
    leftLayout->addWidget(formTitle);

    QFormLayout* formLayout = new QFormLayout();
    
    amountInput = new QLineEdit(this);
    amountInput->setPlaceholderText("0.00");
    formLayout->addRow("Kwota (PLN):", amountInput);

    categoryComboBox = new QComboBox(this);
    formLayout->addRow("Kategoria:", categoryComboBox);

    transactionTypeComboBox = new QComboBox(this);
    formLayout->addRow("Typ tranzakcji:", transactionTypeComboBox);

    descriptionInput = new QLineEdit(this);
    descriptionInput->setPlaceholderText("np. Zakupy w sklepie");
    formLayout->addRow("Opis:", descriptionInput);

    leftLayout->addLayout(formLayout);

    addTransactionButton = new QPushButton("Dodaj transakcję", this);
    leftLayout->addWidget(addTransactionButton);
    leftLayout->addStretch(); // Spycha elementy do góry

    // ================= PRAWY PANEL: TABELA =================
    QVBoxLayout* rightLayout = new QVBoxLayout();
    QLabel* tableTitle = new QLabel("Historia transakcji", this);
    tableTitle->setStyleSheet("font-weight: bold; font-size: 14px;");
    rightLayout->addWidget(tableTitle);

    transactionTable = new QTableWidget(this);
    transactionTable->setColumnCount(4);
    transactionTable->setHorizontalHeaderLabels({"Data", "Kwota", "Kategoria", "Opis"});
    transactionTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    transactionTable->setEditTriggers(QAbstractItemView::NoEditTriggers); // Tabela tylko do odczytu
    rightLayout->addWidget(transactionTable);

    // Łączenie paneli w główny layout (proporcja 1 do 2)
    mainLayout->addLayout(leftLayout, 1);
    mainLayout->addLayout(rightLayout, 2);
}

void MainWindow::loadCategories() {
    categoryComboBox->clear();
    auto categories = categoryService.getAvailableCategories(session);
    for (const auto& cat : categories) {
        // Przechowujemy nazwę jako tekst, a ID kategorii ukrywamy w QVariant (userData)
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
    transactionTable->setRowCount(0); // Czyszczenie tabeli

    for (int i = 0; i < history.size(); ++i) {
        transactionTable->insertRow(i);
        
        // Wyciągamy nazwę kategorii po jej ID, żeby w tabeli nie wyświetlać cyfry
        auto catOpt = categoryService.getAvailableCategories(session);
        QString catName = "Nieznana";
        for(const auto& c : catOpt) {
            if(c.getId() == history[i].getCategoryId()) {
                catName = QString::fromStdString(c.getName());
                break;
            }
        }

        transactionTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(history[i].getDate())));
        transactionTable->setItem(i, 1, new QTableWidgetItem(QString::number(history[i].getAmount(), 'f', 2) + " PLN"));
        transactionTable->setItem(i, 2, new QTableWidgetItem(catName));
        transactionTable->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(history[i].getDescription())));
    }
}

void MainWindow::handleAddTransaction() {
    double amount = amountInput->text().toDouble();
    int catId = categoryComboBox->currentData().toInt();
    TransactionType type = static_cast<TransactionType>(transactionTypeComboBox->currentData().toInt());
    std::string description = descriptionInput->text().toStdString();
    std::string currentDate = QDate::currentDate().toString("yyyy-MM-dd").toStdString();
    
    if (transactionService.addTransaction(amount, catId, currentDate, description, RecurrenceInterval::NONE, session, type)) {
        refreshTransactionHistory();
        amountInput->clear();
        descriptionInput->clear();
    } else {
        QMessageBox::warning(this, "Błąd", "Nie udało się dodać transakcji. Sprawdź poprawność kwoty.");
    }
}