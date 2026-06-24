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

    // 1. Inicjalizacja warstwy danych
    InMemoryUserRepository      userRepo;
    InMemoryCategoryRepository  categoryRepo;
    InMemoryTransactionRepository transactionRepo;
    UserValidator               userValidator;

    // 2. Inicjalizacja warstwy biznesowej
    AuthService         authService(userRepo, userValidator);
    CategoryService     categoryService(categoryRepo);
    TransactionService  transactionService(transactionRepo, categoryRepo);

    // Zapewniamy bazowe kategorie na starcie
    categoryService.initializeDefaultCategories();

    // 3. Uruchomienie okna logowania
    LoginWindow loginWindow(authService);
    loginWindow.show();

    // Wskaźnik na główne okno (na razie puste, stworzymy je dynamicznie po logowaniu)
    MainWindow* mainWindow = nullptr;

    // 4. Magia Qt: Reakcja na poprawne logowanie
    QObject::connect(&loginWindow, &LoginWindow::loginSuccessful, [&](const Session& session) {
        loginWindow.close(); // Zamykamy okno logowania

        // Tworzymy główne okno programu i przekazujemy mu serwisy oraz aktywną sesję
        mainWindow = new MainWindow(session, transactionService, categoryService);
        mainWindow->show();
    });

    int result = a.exec();

    // Sprzątanie pamięci po zakończeniu pętli aplikacji
    if (mainWindow) {
        delete mainWindow;
    }

    return result;
}