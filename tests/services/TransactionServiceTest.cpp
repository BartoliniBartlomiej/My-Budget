#include <gtest/gtest.h>
#include "services/TransactionService.hpp"
#include "repositories/InMemoryTransactionRepository.hpp"
#include "repositories/InMemoryCategoryRepository.hpp"

TEST(TransactionServiceTest, AddsValidTransaction)
{
    InMemoryTransactionRepository tRepo;
    InMemoryCategoryRepository cRepo;
    TransactionService tService(tRepo, cRepo);

    Category globalCategory("Food", CategoryType::FOOD, 0);
    cRepo.add(globalCategory);

    auto availableCategories = cRepo.getByUserId(0);
    ASSERT_FALSE(availableCategories.empty());
    int assignedCategoryId = availableCategories[0].getId();

    Session session(1, "user1");

    EXPECT_TRUE(
        tService.addTransaction(
            25.50,
            assignedCategoryId,
            "2026-06-24",
            "shopping",
            RecurrenceInterval::NONE,
            session));
}

TEST(TransactionServiceTest, RejectsNegativeAmountTransaction)
{
    InMemoryTransactionRepository tRepo;
    InMemoryCategoryRepository cRepo;
    TransactionService tService(tRepo, cRepo);

    Category globalCategory("food", CategoryType::FOOD, 0);
    cRepo.add(globalCategory);

    auto availableCategories = cRepo.getByUserId(0);
    ASSERT_FALSE(availableCategories.empty());
    int assignedCategoryId = availableCategories[0].getId();

    Session session(1, "user1");

    EXPECT_FALSE(
        tService.addTransaction(
            -5.0,
            assignedCategoryId,
            "2026-06-24",
            "error",
            RecurrenceInterval::NONE,
            session));
}

TEST(TransactionServiceTest, ReturnsOnlyValidTransactionsInHistory)
{
    InMemoryTransactionRepository tRepo;
    InMemoryCategoryRepository cRepo;
    TransactionService tService(tRepo, cRepo);

    Category globalCategory("food", CategoryType::FOOD, 0);
    cRepo.add(globalCategory);

    auto availableCategories = cRepo.getByUserId(0);
    ASSERT_FALSE(availableCategories.empty());
    int assignedCategoryId = availableCategories[0].getId();

    Session session(1, "user1");

    tService.addTransaction(25.50, assignedCategoryId, "2026-06-24", "shopping", RecurrenceInterval::NONE, session);

    tService.addTransaction(-5.0, assignedCategoryId, "2026-06-24", "error", RecurrenceInterval::NONE, session);

    auto history = tService.getTransactionHistory(session);

    EXPECT_EQ(history.size(), 1);
}

TEST(TransactionServiceTest, TransactionHistoryContainsCorrectAmount)
{
    InMemoryTransactionRepository tRepo;
    InMemoryCategoryRepository cRepo;
    TransactionService tService(tRepo, cRepo);

    Category globalCategory("food", CategoryType::FOOD, 0);
    cRepo.add(globalCategory);

    auto availableCategories = cRepo.getByUserId(0);
    ASSERT_FALSE(availableCategories.empty());
    int assignedCategoryId = availableCategories[0].getId();

    Session session(1, "user1");

    tService.addTransaction(25.50, assignedCategoryId, "2026-06-24", "Shopping", RecurrenceInterval::NONE, session);

    auto history = tService.getTransactionHistory(session);

    ASSERT_EQ(history.size(), 1);
    EXPECT_DOUBLE_EQ(history[0].getAmount(), 25.50);
}