cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CXX_EXTENSIONS ON)

project(curseu LANGUAGES CXX)

add_executable(${CMAKE_PROJECT_NAME}
    src/main.cpp
)

set(CURSES_NEED_NCURSES TRUE)

find_package(Curses REQUIRED)
find_library(MENU_LIBRARY REQUIRED menu)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    "src/"
    ${CURSES_INCLUDE_DIR}
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    ${MENU_LIBRARY}
    ${CURSES_LIBRARIES}
)
