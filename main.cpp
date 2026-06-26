#include <QApplication>
#include "include/database/DatabaseManager.hpp"
#include "include/repositories/SqliteUserRepository.hpp"
#include "include/repositories/SqliteCategoryRepository.hpp"
#include "include/repositories/SqliteTransactionRepository.hpp"
#include "include/validators/UserValidator.hpp"
#include "include/services/AuthService.hpp"
#include "include/services/CategoryService.hpp"
#include "include/services/TransactionService.hpp"
#include "include/gui/LoginWindow.hpp"
#include "include/gui/MainWindow.hpp"
#include <QMessageBox>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    if (!DatabaseManager::getInstance().init("budget.db")) {
        QMessageBox::critical(nullptr, "Error", "Failed to initialize database!");
        return -1;
    }

    SqliteUserRepository        userRepo;
    SqliteCategoryRepository    categoryRepo;
    SqliteTransactionRepository transactionRepo;
    UserValidator               userValidator;

    AuthService        authService(userRepo, userValidator);
    CategoryService    categoryService(categoryRepo);
    TransactionService transactionService(transactionRepo, categoryRepo);

    categoryService.initializeDefaultCategories();

    LoginWindow* loginWindow = new LoginWindow(authService);
    MainWindow*  mainWindow  = nullptr;

    auto showLogin = [&]() {
        DatabaseManager::getInstance().clearLastUser();
        if (mainWindow) { mainWindow->hide(); }
        loginWindow->show();
    };

    auto showMain = [&](const Session& session) {
        DatabaseManager::getInstance().saveLastUser(session.getUserId());
        loginWindow->hide();
        mainWindow = new MainWindow(session, transactionService, categoryService);
        QObject::connect(mainWindow, &MainWindow::logoutRequested, showLogin);
        mainWindow->show();
    };

    QObject::connect(loginWindow, &LoginWindow::loginSuccessful, showMain);

    int lastUserId = DatabaseManager::getInstance().loadLastUserId();
    if (lastUserId != -1) {
        auto userOpt = userRepo.getById(lastUserId);
        if (userOpt.has_value()) {
            showMain(Session(userOpt->getId(), userOpt->getLogin()));
        } else {
            loginWindow->show();
        }
    } else {
        loginWindow->show();
    }

    int result = a.exec();
    delete mainWindow;
    delete loginWindow;
    return result;
}