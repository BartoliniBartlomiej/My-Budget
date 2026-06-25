#include "../../include/gui/MainWindow.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QMessageBox>
#include <QHeaderView>
#include <QDate>
#include <QFrame>

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
    setWindowTitle(QString("My Budget — %1").arg(QString::fromStdString(session.getUsername())));
    resize(900, 560);
    setMinimumSize(700, 420);

    // ── Global palette ──────────────────────────────────────────────────────
    setStyleSheet(R"(
        QMainWindow, QWidget#central {
            background-color: #F7F8FA;
        }

        /* ── Left panel card ── */
        QWidget#leftCard {
            background-color: #FFFFFF;
            border-radius: 12px;
            border: 1px solid #E5E8EF;
        }

        /* ── Section labels ── */
        QLabel#sectionTitle {
            font-family: "Inter", "Segoe UI", sans-serif;
            font-size: 13px;
            font-weight: 600;
            color: #0F1117;
            letter-spacing: 0.2px;
        }

        /* ── Form row labels ── */
        QLabel {
            font-family: "Inter", "Segoe UI", sans-serif;
            font-size: 12px;
            color: #6B7280;
        }

        /* ── Inputs ── */
        QLineEdit, QComboBox, QTextEdit {
            font-family: "Inter", "Segoe UI", sans-serif;
            font-size: 13px;
            color: #0F1117;
            background-color: #F7F8FA;
            border: 1px solid #E5E8EF;
            border-radius: 7px;
            padding: 7px 10px;
            min-height: 18px;
        }
        QLineEdit:focus, QComboBox:focus {
            border: 1px solid #4F6EF7;
            background-color: #FFFFFF;
            outline: none;
        }
        QLineEdit::placeholder {
            color: #B0B7C3;
        }
        QComboBox::drop-down {
            border: none;
            width: 24px;
        }
        QComboBox::down-arrow {
            image: none;
            width: 0;
        }
        QComboBox QAbstractItemView {
            background: #FFFFFF;
            border: 1px solid #E5E8EF;
            border-radius: 7px;
            selection-background-color: #EEF2FF;
            selection-color: #4F6EF7;
            font-size: 13px;
            color: #0F1117;
        }

        /* ── Primary button ── */
        QPushButton#addBtn {
            font-family: "Inter", "Segoe UI", sans-serif;
            font-size: 13px;
            font-weight: 600;
            color: #FFFFFF;
            background-color: #4F6EF7;
            border: none;
            border-radius: 8px;
            padding: 10px 0;
        }
        QPushButton#addBtn:hover {
            background-color: #3B58E8;
        }
        QPushButton#addBtn:pressed {
            background-color: #2E47D0;
        }

        /* ── Table ── */
        QTableWidget {
            background-color: #FFFFFF;
            border: 1px solid #E5E8EF;
            border-radius: 12px;
            gridline-color: #F0F2F5;
            font-family: "Inter", "Segoe UI", sans-serif;
            font-size: 12px;
            color: #0F1117;
            selection-background-color: #EEF2FF;
            selection-color: #0F1117;
        }
        QHeaderView::section {
            background-color: #F7F8FA;
            color: #6B7280;
            font-family: "Inter", "Segoe UI", sans-serif;
            font-size: 11px;
            font-weight: 600;
            letter-spacing: 0.5px;
            text-transform: uppercase;
            border: none;
            border-bottom: 1px solid #E5E8EF;
            padding: 10px 12px;
        }
        QTableWidget::item {
            padding: 9px 12px;
            border: none;
        }
        QTableWidget::item:alternate {
            background-color: #FAFBFC;
        }
        QScrollBar:vertical {
            background: #F7F8FA;
            width: 6px;
            margin: 0;
            border-radius: 3px;
        }
        QScrollBar::handle:vertical {
            background: #D1D5DB;
            border-radius: 3px;
            min-height: 30px;
        }
        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            height: 0;
        }
    )");

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setObjectName("central");
    setCentralWidget(centralWidget);

    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(16);

    // ================= LEFT PANEL (card) =================
    QWidget* leftCard = new QWidget(this);
    leftCard->setObjectName("leftCard");

    QVBoxLayout* leftLayout = new QVBoxLayout(leftCard);
    leftLayout->setContentsMargins(24, 24, 24, 24);
    leftLayout->setSpacing(14);

    QLabel* formTitle = new QLabel("New Transaction", leftCard);
    formTitle->setObjectName("sectionTitle");
    leftLayout->addWidget(formTitle);

    // thin divider
    QFrame* divider = new QFrame(leftCard);
    divider->setFrameShape(QFrame::HLine);
    divider->setStyleSheet("color: #E5E8EF;");
    leftLayout->addWidget(divider);

    QFormLayout* formLayout = new QFormLayout();
    formLayout->setRowWrapPolicy(QFormLayout::WrapAllRows);
    formLayout->setVerticalSpacing(10);
    formLayout->setHorizontalSpacing(0);
    formLayout->setLabelAlignment(Qt::AlignLeft);

    amountInput = new QLineEdit(leftCard);
    amountInput->setPlaceholderText("0.00");
    formLayout->addRow("Amount (PLN)", amountInput);

    categoryComboBox = new QComboBox(leftCard);
    formLayout->addRow("Category", categoryComboBox);

    transactionTypeComboBox = new QComboBox(leftCard);
    formLayout->addRow("Type", transactionTypeComboBox);

    titleInput = new QLineEdit(leftCard);
    titleInput->setPlaceholderText("e.g. Groceries");
    formLayout->addRow("Title", titleInput);

    descriptionInput = new QTextEdit(leftCard);
    descriptionInput->setPlaceholderText("Optional note");
    descriptionInput->setMinimumHeight(70);
    formLayout->addRow("Note", descriptionInput );

    leftLayout->addLayout(formLayout);
    leftLayout->addSpacing(4);

    addTransactionButton = new QPushButton("Add Transaction", leftCard);
    addTransactionButton->setObjectName("addBtn");
    addTransactionButton->setCursor(Qt::PointingHandCursor);
    leftLayout->addWidget(addTransactionButton);
    leftLayout->addStretch();

    // ================= RIGHT PANEL (table) =================
    QVBoxLayout* rightLayout = new QVBoxLayout();
    rightLayout->setSpacing(10);
    rightLayout->setContentsMargins(0, 0, 0, 0);

    QLabel* tableTitle = new QLabel("Transaction History", this);
    tableTitle->setObjectName("sectionTitle");
    rightLayout->addWidget(tableTitle);

    transactionTable = new QTableWidget(this);
    transactionTable->setColumnCount(4);
    transactionTable->setHorizontalHeaderLabels({"Date", "Amount", "Category", "Title"});
    transactionTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    transactionTable->horizontalHeader()->setHighlightSections(false);
    transactionTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    transactionTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    transactionTable->setAlternatingRowColors(true);
    transactionTable->setShowGrid(false);
    transactionTable->verticalHeader()->hide();
    transactionTable->setFrameShape(QFrame::NoFrame);
    rightLayout->addWidget(transactionTable);

    mainLayout->addWidget(leftCard, 1);
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
        case TransactionType::INCOME:  return "Income";
        case TransactionType::EXPENSE: return "Expense";
        default:                       return "Unknown";
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
        for (const auto& c : catOpt) {
            if (c.getId() == history[i].getCategoryId()) {
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
    double amount       = amountInput->text().toDouble();
    int catId           = categoryComboBox->currentData().toInt();
    TransactionType type = static_cast<TransactionType>(transactionTypeComboBox->currentData().toInt());
    std::string title   = titleInput->text().toStdString();
    QString qDescription = descriptionInput->toPlainText();
    std::string description = qDescription.toStdString();
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