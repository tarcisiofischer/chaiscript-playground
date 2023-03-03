cmake_minimum_required(VERSION 3.22)
project(chaiscript_playground)

set(CMAKE_CXX_STANDARD 14)

add_executable(chaiscript_playground
    main.cc
)

target_include_directories(chaiscript_playground PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ChaiScript/include/)
