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
    int          getId()     const {   return id;    }
    std::string  getName()   const {   return name;  }
    CategoryType getType()   const {   return type;  }
    int          getUserId() const {   return userId;}

    void setId(int id) { this->id = id; }
};