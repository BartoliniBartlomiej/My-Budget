#pragma once

#include <vector>
#include <optional>
#include "../models/Category.hpp"

class ICategoryRepository {
public:
    virtual ~ICategoryRepository() = default;

    virtual void                    add(const Category& category)       = 0;
    virtual std::optional<Category> getById(int id)               const = 0;
    virtual std::vector<Category>   getByUserId(int userId)       const = 0;
};