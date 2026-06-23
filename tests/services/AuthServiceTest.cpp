#include <gtest/gtest.h>
#include "services/AuthService.hpp"
#include "repositories/InMemoryUserRepository.hpp"
#include "validators/UserValidator.hpp"

TEST(AuthServiceTest, Register) {
    InMemoryUserRepository repo;
    UserValidator validator;
    AuthService authService(repo, validator);

    EXPECT_TRUE(authService.registerUser("new_user", "password123"));
}

TEST(AuthServiceTest, DuplicateRegister) {
    InMemoryUserRepository repo;
    UserValidator validator;
    AuthService authService(repo, validator);

    auto user = authService.registerUser("new_user", "password123");
    EXPECT_FALSE(authService.registerUser("new_user", "password123"));
}

TEST(AuthServiceTest, LogginWithIncorrectPassword) {
    InMemoryUserRepository repo;
    UserValidator validator;
    AuthService authService(repo, validator);
    
    auto user = authService.registerUser("new_user", "password123");
    auto failedSession = authService.loginUser("new_user", "password000");

    EXPECT_FALSE(failedSession.has_value());
    
}

TEST(AuthServiceTest, LoginShouldBeSuccess) {
    InMemoryUserRepository repo;
    UserValidator validator;
    AuthService authService(repo, validator);

    auto registerUser = authService.registerUser("new_user", "password123");
    auto successSession = authService.loginUser("new_user", "password123");

    ASSERT_TRUE(successSession.has_value());
    EXPECT_EQ(successSession->getUsername(), "new_user");
    EXPECT_TRUE(successSession->isLoggedIn());
}
