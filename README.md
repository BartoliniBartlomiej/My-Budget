# Spending Manager


```
BudgetManager/
├── CMakeLists.txt
├── README.md
│
├── include/
│   └── budget/
│       ├── models/
│       │   ├── User.hpp ✅
│       │   ├── Category.hpp ✅
│       │   ├── Transaction.hp ✅
│       │   ├── Budget.hpp ✅
│       │   └── Session.hpp
│       ├── enums/
│       │   ├── TransactionType.hpp
│       │   ├── RecurrenceInterval.hpp
│       │   └── CategoryType.hpp
│       ├── validators/
│       │   ├── UserValidator.hpp
│       │   ├── TransactionValidator.hpp
│       │   └── BudgetValidator.hpp
│       ├── repositories/
│       │   ├── IUserRepository.hpp
│       │   ├── ITransactionRepository.hpp
│       │   ├── ICategoryRepository.hpp
│       │   └── IBudgetRepository.hpp
│       ├── services/
│       │   ├── AuthService.hpp
│       │   ├── TransactionService.hpp
│       │   ├── CategoryService.hpp
│       │   ├── BudgetService.hpp
│       │   └── ReportService.hpp
│       ├── dto/
│       │   ├── SummaryDTO.hpp
│       │   ├── BudgetStatusDTO.hpp
│       │   ├── MonthlySummaryDTO.hpp
│       │   ├── CategoryBreakdownDTO.hpp
│       │   └── MonthBalanceDTO.hpp
│       └── cli/
│           ├── CLIApp.hpp
│           ├── AuthView.hpp
│           ├── TransactionView.hpp
│           ├── BudgetView.hpp
│           ├── ReportView.hpp
│           └── InputHelper.hpp
│
├── src/
│   ├── models/
│   │   ├── User.cpp
│   │   ├── Category.cpp
│   │   ├── Transaction.cpp
│   │   └── Budget.cpp
│   ├── validators/
│   │   ├── UserValidator.cpp
│   │   ├── TransactionValidator.cpp
│   │   └── BudgetValidator.cpp
│   ├── repositories/
│   │   ├── InMemoryUserRepository.cpp
│   │   ├── InMemoryTransactionRepository.cpp
│   │   ├── InMemoryCategoryRepository.cpp
│   │   └── InMemoryBudgetRepository.cpp
│   ├── services/
│   │   ├── AuthService.cpp
│   │   ├── TransactionService.cpp
│   │   ├── CategoryService.cpp
│   │   ├── BudgetService.cpp
│   │   └── ReportService.cpp
│   └── cli/
│       ├── CLIApp.cpp
│       ├── AuthView.cpp
│       ├── TransactionView.cpp
│       ├── BudgetView.cpp
│       ├── ReportView.cpp
│       └── InputHelper.cpp
│
├── tests/
│   ├── CMakeLists.txt
│   ├── validators/
│   │   ├── UserValidatorTest.cpp
│   │   ├── TransactionValidatorTest.cpp
│   │   └── BudgetValidatorTest.cpp
│   ├── repositories/
│   │   ├── InMemoryUserRepositoryTest.cpp
│   │   └── InMemoryTransactionRepositoryTest.cpp
│   └── services/
│       ├── AuthServiceTest.cpp
│       ├── TransactionServiceTest.cpp
│       └── BudgetServiceTest.cpp
│
└── main.cpp
```