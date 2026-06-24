#include "../../include/gui/LoginWindow.hpp"
#include <QMessageBox>

LoginWindow::LoginWindow(AuthService& auth, QWidget* parent) 
    : QWidget(parent), authService(auth) {
    setupUi();
    
    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::handleLogin);
    connect(registerButton, &QPushButton::clicked, this, &LoginWindow::handleRegister);
}

void LoginWindow::setupUi() {
    setWindowTitle("Spending Manager - Logowanie");
    resize(350, 250);

    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* titleLabel = new QLabel("Witaj w Spending Manager", this);
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
    passwordInput->setPlaceholderText("Hasło");
    passwordInput->setEchoMode(QLineEdit::Password);
    layout->addWidget(passwordInput);

    loginButton = new QPushButton("Zaloguj się", this);
    layout->addWidget(loginButton);

    registerButton = new QPushButton("Zarejestruj nowe konto", this);
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
        statusLabel->setText("Błędny login lub hasło!");
    }
}

void LoginWindow::handleRegister() {
    std::string login = loginInput->text().toStdString();
    std::string password = passwordInput->text().toStdString();

    if (authService.registerUser(login, password)) {
        QMessageBox::information(this, "Sukces", "Konto zostało utworzone! Możesz się teraz zalogować.");
        statusLabel->setText("");
    } else {
        statusLabel->setText("Rejestracja nieudana (min. 3 zn. login, 6 zn. hasło)!");
    }
}