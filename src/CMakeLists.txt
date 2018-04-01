cmake_minimum_required(VERSION 3.0)

project(Sudoku)

set( CMAKE_CXX_EXTENSIONS ON )

include_directories(./)

include_directories(TEST)

add_subdirectory(Sudoku)
include_directories(Sudoku)


add_subdirectory (CardGame)
include_directories(CardGame)
include_directories(CardGame/event_queue/)
include_directories(CardGame/game_basic/)
include_directories(CardGame/poker/)
include_directories(CardGame/poker_ddz/)
include_directories(CardGame/poker_ddz/ai)
include_directories(CardGame/poker_ddz/player)
include_directories(CardGame/poker_ddz/rule)

############################################# APP

add_executable(ddz APP/ddz.cpp)
target_link_libraries (ddz CardGame)
# target_link_libraries (ddz Dragon)

add_executable(sudoku_read TEST/sudoku_read.cpp)
add_executable(sudoku_check TEST/sudoku_check.cpp)
target_link_libraries (sudoku_check Sudoku)

