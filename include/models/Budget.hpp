#pragma once

#include <string>

class Budget {
private:
    int         id;
    int         userId;
    int         categoryId;
    double      limitAmount;
    std::string monthYear;

public:
    int         getId()          const {   return id;            }
    int         getUserId()      const {   return userId;        }
    int         getCategoryId()  const {   return categoryId;    }
    double      getLimitAmount() const {   return limitAmount;   }
    std::string getMonthYear()   const {   return monthYear;     }
};