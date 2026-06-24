#pragma once

#include "ICategoryRepository.hpp"

class InMemoryCategoryRepository : public ICategoryRepository {
private:
    std::vector<Category> categories;
    int                   nextId = 1;

public:
    void                    add(const Category& category) override;
    std::optional<Category> getById(int id)         const override;
    std::vector<Category>   getByUserId(int userId) const override;
};