include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE TEST_SOURCES "*.cpp")

add_executable(run_tests ${TEST_SOURCES})

target_link_libraries(run_tests PRIVATE app_lib gtest_main Qt6::Core)

include(GoogleTest)
gtest_discover_tests(run_tests)