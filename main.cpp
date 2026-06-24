#include <QApplication>
#include "include/repositories/InMemoryUserRepository.hpp"
#include "include/validators/UserValidator.hpp"
#include "include/services/AuthService.hpp"
#include "include/gui/LoginWindow.hpp"
#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    InMemoryUserRepository userRepo;
    UserValidator          userValidator;
    AuthService            authService(userRepo, userValidator);

    LoginWindow loginWindow(authService);
    loginWindow.show();

    QObject::connect(&loginWindow, &LoginWindow::loginSuccessful, [](const Session& session) {
        qDebug() << "Succes. Logged as:" << QString::fromStdString(session.getUsername());
    });

    return a.exec();
}   