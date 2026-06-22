#include <iostream>

#include "include/models/User.hpp"

int main() {
    User u("test_user", "password123");
    Transaction t1(1, 1, CategoryType::SALARY, 100.0, "Salary", "Weekly salary", "2024-06-01", RecurrenceInterval::WEEKLY, "2024-12-31");
    Transaction t2(1, 1, CategoryType::FOOD, 50.0, "Groceries", "Aldi groceries", "2024-06-02", RecurrenceInterval::NONE, "");
    u.addTransaction(t1);
    u.addTransaction(t2);
    u.printTransactions();

    return 0;
}