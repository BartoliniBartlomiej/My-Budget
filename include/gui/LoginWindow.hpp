#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include "../services/AuthService.hpp"

class LoginWindow : public QWidget {
    Q_OBJECT 

private:
    AuthService& authService;

    QLineEdit* loginInput;
    QLineEdit* passwordInput;
    QPushButton* loginButton;
    QPushButton* registerButton;
    QLabel* statusLabel;

    void setupUi();

private slots:
    void handleLogin();
    void handleRegister();

signals:
    void loginSuccessful(const Session& session);
    
public:
    LoginWindow(AuthService& auth, QWidget* parent = nullptr);
};