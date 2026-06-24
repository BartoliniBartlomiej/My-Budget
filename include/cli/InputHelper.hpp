#pragma once

#include <string>

class InputHelper {
public:
    static std::string readString(const std::string& prompt);
    
    static double readDouble(const std::string& prompt);
    
    static int readInt(const std::string& prompt);
};