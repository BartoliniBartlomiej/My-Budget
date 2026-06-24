#include "../../include/repositories/InMemoryCategoryRepository.hpp"

void InMemoryCategoryRepository::add(const Category& category) {
    Category newCategory = category;

    newCategory.setId(nextId++);
    
    categories.push_back(newCategory);
}

std::optional<Category> InMemoryCategoryRepository::getById(int id) const {
    for (const auto& category : categories) {
        if (category.getId() == id) {
            return category;
        }
    }
    return std::nullopt;
}

std::vector<Category> InMemoryCategoryRepository::getByUserId(int userId) const {
    std::vector<Category> userCategories;
    for (const auto& category : categories) {
        if (category.getUserId() == 0 || category.getUserId() == userId) {
            userCategories.push_back(category);
        }
    }
    return userCategories;
}