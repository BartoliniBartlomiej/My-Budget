#include <QApplication>
#include "include/database/DatabaseManager.hpp"
#include "include/repositories/SqliteUserRepository.hpp"
#include "include/repositories/SqliteCategoryRepository.hpp"
#include "include/repositories/SqliteTransactionRepository.hpp" // Nowy nagłówek
#include "include/validators/UserValidator.hpp"
#include "include/services/AuthService.hpp"
#include "include/services/CategoryService.hpp"
#include "include/services/TransactionService.hpp"
#include "include/gui/LoginWindow.hpp"
#include "include/gui/MainWindow.hpp"
#include <QMessageBox>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // 1. Inicjalizacja bazy
    if (!DatabaseManager::getInstance().init("budget.db")) {
        QMessageBox::critical(nullptr, "Blad krytyczny", "Nie udalo sie zainicjalizowac bazy danych!");
        return -1;
    }

    // 2. Warstwa danych — WSZYSTKO NA SQLITE!
    SqliteUserRepository        userRepo; 
    SqliteCategoryRepository    categoryRepo;
    SqliteTransactionRepository transactionRepo; // Zmiana!
    UserValidator               userValidator;

    // 3. Warstwa biznesowa
    AuthService         authService(userRepo, userValidator);
    CategoryService     categoryService(categoryRepo);
    TransactionService  transactionService(transactionRepo, categoryRepo);

    categoryService.initializeDefaultCategories();

    // 4. GUI
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