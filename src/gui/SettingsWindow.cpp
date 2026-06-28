#include "../../include/gui/SettingsWindow.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>

SettingsWindow::SettingsWindow(Session& activeSession, QWidget* parent)
    : QDialog(parent), session(activeSession) {
    setupUi();

    connect(saveButton, &QPushButton::clicked, this, &SettingsWindow::handleSave);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

void SettingsWindow::setupUi() {
    setWindowTitle("Ustawienia");
    resize(300, 150);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QFormLayout* formLayout = new QFormLayout();

    currencyComboBox = new QComboBox(this);
    currencyComboBox->addItem("PLN", static_cast<int>(Currency::PLN));
    currencyComboBox->addItem("USD", static_cast<int>(Currency::USD));
    currencyComboBox->addItem("EUR", static_cast<int>(Currency::EUR));
    currencyComboBox->addItem("GBP", static_cast<int>(Currency::GBP));

    int currentIndex = currencyComboBox->findData(static_cast<int>(session.getCurrency()));
    if (currentIndex != -1) {
        currencyComboBox->setCurrentIndex(currentIndex);
    }

    formLayout->addRow("Currency:", currencyComboBox);
    mainLayout->addLayout(formLayout);

    QHBoxLayout* btnLayout = new QHBoxLayout();
    saveButton = new QPushButton("Save", this);
    cancelButton = new QPushButton("Cancel", this);
    
    btnLayout->addWidget(saveButton);
    btnLayout->addWidget(cancelButton);
    mainLayout->addLayout(btnLayout);
}

void SettingsWindow::handleSave() {
    int selectedCurrencyInt = currencyComboBox->currentData().toInt();
    Currency selectedCurrency = static_cast<Currency>(selectedCurrencyInt);
    
    session.setCurrency(selectedCurrency);

    accept();
}