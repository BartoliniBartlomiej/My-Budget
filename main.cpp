#include "include/repositories/InMemoryUserRepository.hpp"
#include "include/repositories/InMemoryCategoryRepository.hpp"
#include "include/repositories/InMemoryTransactionRepository.hpp"
#include "include/validators/UserValidator.hpp"
#include "include/services/AuthService.hpp"
#include "include/services/CategoryService.hpp"
#include "include/services/TransactionService.hpp"
#include "include/cli/CLIApp.hpp"

int main() {
    InMemoryUserRepository      userRepo;
    InMemoryCategoryRepository  categoryRepo;
    InMemoryTransactionRepository transactionRepo;
    UserValidator               userValidator;

    AuthService         authService(userRepo, userValidator);
    CategoryService     categoryService(categoryRepo);
    TransactionService  transactionService(transactionRepo, categoryRepo);

    CLIApp app(authService, categoryService, transactionService);
    app.run();

    return 0;
}