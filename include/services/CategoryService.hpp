#pragma once

#include <vector>
#include <string>
#include "../repositories/ICategoryRepository.hpp"
#include "../models/Session.hpp"
#include "../enums/Enums.hpp"

class CategoryService {
private:
    ICategoryRepository& categoryRepository;
    
public:
    CategoryService(ICategoryRepository& repo) : categoryRepository(repo) {}

    void initializeDefaultCategories();

    bool createCategory(const std::string& name, CategoryType type, const Session& session);

    std::vector<Category> getAvailableCategories(const Session& session) const;
};