#include "../../include/services/CategoryService.hpp"

void CategoryService::initializeDefaultCategories() {
    if (categoryRepository.getByUserId(0).empty()) {
        categoryRepository.add(Category("Food", CategoryType::FOOD, 0));
        categoryRepository.add(Category("Housing", CategoryType::HOUSING, 0));
        categoryRepository.add(Category("Transport", CategoryType::TRANSPORT, 0));
        categoryRepository.add(Category("Entertainment", CategoryType::ENTERTAINMENT, 0));
        categoryRepository.add(Category("Salary", CategoryType::SALARY, 0));
    }
}

bool CategoryService::createCategory(const std::string& name, CategoryType type, const Session& session) {
    if (!session.isLoggedIn()) {
        return false;
    }
    if (name.empty()) {
        return false;
    }

    Category newCategory(name, type, session.getUserId());
    categoryRepository.add(newCategory);
    return true;
}

std::vector<Category> CategoryService::getAvailableCategories(const Session& session) const {
    if (!session.isLoggedIn()) {
        return {};
    }
    return categoryRepository.getByUserId(session.getUserId());
}