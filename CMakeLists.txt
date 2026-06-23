cmake_minimum_required(VERSION 3.15)
project(SpendingManager VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE APP_SOURCES 
    "src/*.cpp"
)

add_library(app_lib ${APP_SOURCES})
target_include_directories(app_lib PUBLIC include)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE app_lib)

enable_testing()
add_subdirectory(tests)