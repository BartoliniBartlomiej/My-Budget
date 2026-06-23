#include <gtest/gtest.h>
#include "validators/UserValidator.hpp"

TEST(UserValidatorTest, ValidateLoginCorrectly) {
    UserValidator validator;
    
    EXPECT_TRUE(validator.validateLogin("steve101"));
    EXPECT_FALSE(validator.validateLogin("bo")); // too short
    EXPECT_FALSE(validator.validateLogin(""));   // Empty
}

TEST(UserValidatorTest, ValidatePasswordCorrectly) {
    UserValidator validator;
    
    EXPECT_TRUE(validator.validatePassword("password123"));
    EXPECT_FALSE(validator.validatePassword("123")); // Too short
}