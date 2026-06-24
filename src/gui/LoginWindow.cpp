#include "../../include/gui/LoginWindow.hpp"
#include <QMessageBox>

LoginWindow::LoginWindow(AuthService& auth, QWidget* parent) 
    : QWidget(parent), authService(auth) {
    setupUi();
    
    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::handleLogin);
    connect(registerButton, &QPushButton::clicked, this, &LoginWindow::handleRegister);
}

void LoginWindow::setupUi() {
    setWindowTitle("My Budget - Login");
    resize(350, 250);

    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* titleLabel = new QLabel("My Budget", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont font = titleLabel->font();
    font.setPointSize(16);
    font.setBold(true);
    titleLabel->setFont(font);
    layout->addWidget(titleLabel);

    loginInput = new QLineEdit(this);
    loginInput->setPlaceholderText("Login");
    layout->addWidget(loginInput);

    passwordInput = new QLineEdit(this);
    passwordInput->setPlaceholderText("Password");
    passwordInput->setEchoMode(QLineEdit::Password);
    layout->addWidget(passwordInput);

    loginButton = new QPushButton("Log in", this);
    layout->addWidget(loginButton);

    registerButton = new QPushButton("Sign in", this);
    layout->addWidget(registerButton);

    statusLabel = new QLabel("", this);
    statusLabel->setStyleSheet("color: red;");
    statusLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(statusLabel);
}

void LoginWindow::handleLogin() {
    std::string login = loginInput->text().toStdString();
    std::string password = passwordInput->text().toStdString();

    auto sessionOpt = authService.loginUser(login, password);

    if (sessionOpt.has_value()) {
        statusLabel->setText("");
        emit loginSuccessful(sessionOpt.value());
    } else {
        statusLabel->setText("Incorrect login or/and password!");
    }
}

void LoginWindow::handleRegister() {
    std::string login = loginInput->text().toStdString();
    std::string password = passwordInput->text().toStdString();

    if (authService.registerUser(login, password)) {
        QMessageBox::information(this, "Success", "Account created. You can log now.");
        statusLabel->setText("");
    } else {
        statusLabel->setText("Failed registration. (min. 3 char. login, 6 char. password)!");
    }
}