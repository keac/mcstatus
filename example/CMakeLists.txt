project (demo)
cmake_minimum_required(VERSION 2.8)

# [Boost]
find_package(Boost 1.59 COMPONENTS system REQUIRED)
if(${Boost_FOUND})
    message(${Boost_INCLUDE_DIRS})
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIR})
endif()
# [Boost end]

add_subdirectory("../" "mcstatus")
include_directories("../include")

set (SOURCES_LIST
    "./src/main.cpp"
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(demo ${SOURCES_LIST})
target_link_libraries(demo mcstatus)
