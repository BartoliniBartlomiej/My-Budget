#pragma once

#include <string>

#include "../enums/Enums.hpp"

class Transaction {
    int id;
    int userId;
    int categoryId;
    CategoryType type;
    double amount;
    std::string title;
    std::string description;
    std::string date;
    RecurrenceInterval recurrence;
    std::string recurrenceEndDate;

public:
    Transaction(double _amount, std::string _title) : amount(_amount), title(_title) {}
    Transaction(int _userId, int _categoryId, CategoryType _type, double _amount, std::string _title, std::string _description, std::string _date, RecurrenceInterval _recurrence = RecurrenceInterval::NONE, std::string _recurrenceEndDate = "")
        : userId(_userId), categoryId(_categoryId), type(_type), amount(_amount), title(_title), description(_description), date(_date), recurrence(_recurrence), recurrenceEndDate(_recurrenceEndDate) {}
    
    int                getId()                const { return id;                }
    int                getUserId()            const { return userId;            }
    int                getCategoryId()        const { return categoryId;        }
    CategoryType       getType()              const { return type;              }
    double             getAmount()            const { return amount;            }
    std::string        getTitle()             const { return title;             }
    std::string        getDescription()       const { return description;       }
    std::string        getDate()              const { return date;              }
    RecurrenceInterval getRecurrence()        const { return recurrence;        }
    std::string        getRecurrenceEndDate() const { return recurrenceEndDate; }

    bool isRecurring() const {
        return recurrence != RecurrenceInterval::NONE;
    }
};