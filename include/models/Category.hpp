#pragma once

#include <string>

#include "../enums/Enums.hpp"

class Category {
private:
    int             id;
    std::string     name;
    CategoryType    type;
    int             userId;

public:
    Category() : id(0), name(""), type(CategoryType::OTHER), userId(0) {}
    Category(std::string _name, CategoryType _type, int _userId) 
        : id(0), name(_name), type(_type), userId(_userId) {}

    int          getId()     const {   return id;    }
    std::string  getName()   const {   return name;  }
    CategoryType getType()   const {   return type;  }
    int          getUserId() const {   return userId;}

    void setId(int id) { this->id = id; }
};