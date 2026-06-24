#include <QApplication>
#include "include/repositories/InMemoryUserRepository.hpp"
#include "include/repositories/InMemoryCategoryRepository.hpp"
#include "include/repositories/InMemoryTransactionRepository.hpp"
#include "include/validators/UserValidator.hpp"
#include "include/services/AuthService.hpp"
#include "include/services/CategoryService.hpp"
#include "include/services/TransactionService.hpp"
#include "include/gui/LoginWindow.hpp"
#include "include/gui/MainWindow.hpp"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    InMemoryUserRepository      userRepo;
    InMemoryCategoryRepository  categoryRepo;
    InMemoryTransactionRepository transactionRepo;
    UserValidator               userValidator;

    AuthService         authService(userRepo, userValidator);
    CategoryService     categoryService(categoryRepo);
    TransactionService  transactionService(transactionRepo, categoryRepo);

    categoryService.initializeDefaultCategories();

    LoginWindow loginWindow(authService);
    loginWindow.show();

    MainWindow* mainWindow = nullptr;

    QObject::connect(&loginWindow, &LoginWindow::loginSuccessful, [&](const Session& session) {
        loginWindow.close();

        mainWindow = new MainWindow(session, transactionService, categoryService);
        mainWindow->show();
    });

    int result = a.exec();

    if (mainWindow) {
        delete mainWindow;
    }

    return result;
}