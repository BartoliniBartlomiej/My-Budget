#pragma once

#include "ICategoryRepository.hpp"
#include <QSqlDatabase>

class SqliteCategoryRepository : public ICategoryRepository {
private:
    std::string typeToString(CategoryType type) const;
    CategoryType stringToType(const std::string& str) const;

public:
    SqliteCategoryRepository() = default;
    ~SqliteCategoryRepository() override = default;

    void add(const Category& category) override;
    std::optional<Category> getById(int id) const override;
    std::vector<Category> getByUserId(int userId) const override;
};