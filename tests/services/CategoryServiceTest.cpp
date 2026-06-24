#include <gtest/gtest.h>
#include "services/CategoryService.hpp"
#include "repositories/InMemoryCategoryRepository.hpp"

TEST(CategoryServiceTest, InitializesDefaultCategories)
{
    InMemoryCategoryRepository repo;
    CategoryService categoryService(repo);

    categoryService.initializeDefaultCategories();

    Session session(42, "smith");

    auto categories = categoryService.getAvailableCategories(session);

    EXPECT_EQ(categories.size(), 7);
}

TEST(CategoryServiceTest, CreatesPrivateCategoryForUser)
{
    InMemoryCategoryRepository repo;
    CategoryService categoryService(repo);

    categoryService.initializeDefaultCategories();

    Session session(42, "smith");

    EXPECT_TRUE(
        categoryService.createCategory(
            "My Hobby",
            CategoryType::ENTERTAINMENT,
            session));
}

TEST(CategoryServiceTest, UserSeesCreatedPrivateCategory)
{
    InMemoryCategoryRepository repo;
    CategoryService categoryService(repo);

    categoryService.initializeDefaultCategories();

    Session session(42, "smith");

    categoryService.createCategory(
        "My Hobby",
        CategoryType::ENTERTAINMENT,
        session);

    auto categories = categoryService.getAvailableCategories(session);

    EXPECT_EQ(categories.size(), 8); // 7 default + 1 private
}

TEST(CategoryServiceTest, PrivateCategoryIsNotVisibleToOtherUsers)
{
    InMemoryCategoryRepository repo;
    CategoryService categoryService(repo);

    categoryService.initializeDefaultCategories();

    Session ownerSession(42, "smith");
    Session anotherSession(99, "tornvalds");

    categoryService.createCategory(
        "My Hobby",
        CategoryType::ENTERTAINMENT,
        ownerSession);

    auto categories = categoryService.getAvailableCategories(anotherSession);

    EXPECT_EQ(categories.size(), 7);
}