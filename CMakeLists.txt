cmake_minimum_required(VERSION 3.27.4)
project(intrprtr_0)

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-wall -g3")

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

FLEX_TARGET(my_lexer
    lexer.l
    ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp
)

BISON_TARGET(my_parser
    parser.y
    ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
    COMPILE_FLAGS "--defines=${CMAKE_CURRENT_BINARY_DIR}/lexer_defines.h"
)

ADD_FLEX_BISON_DEPENDENCY(my_lexer my_parser)

add_executable(${PROJECT_NAME}
    driver.cpp
    driver.hpp
    INode.hpp
    Node.hpp
    Node.cpp
    
    ${BISON_my_parser_OUTPUTS}
    ${FLEX_my_lexer_OUTPUTS}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
     
