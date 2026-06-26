cmake_minimum_required(VERSION 3.16)
project(SpendingManager VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Sql)


file(GLOB_RECURSE APP_SOURCES 
    "src/*.cpp"
    "include/*.hpp"
)

add_library(app_lib ${APP_SOURCES})
target_include_directories(app_lib PUBLIC include)

target_link_libraries(app_lib PUBLIC Qt6::Core Qt6::Widgets Qt6::Sql)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE app_lib Qt6::Widgets Qt6::Sql)

enable_testing()
add_subdirectory(tests)