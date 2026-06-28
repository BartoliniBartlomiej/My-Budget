#pragma once

#include <QDialog>
#include <QComboBox>
#include <QPushButton>
#include "../models/Session.hpp"

class SettingsWindow : public QDialog {
    Q_OBJECT

private:
    Session& session;

    QComboBox* currencyComboBox;
    QPushButton* saveButton;
    QPushButton* cancelButton;

    void setupUi();

private slots:
    void handleSave();

public:
    SettingsWindow(Session& activeSession, QWidget* parent = nullptr);
};