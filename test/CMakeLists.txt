cmake_minimum_required (VERSION 2.8)
project (mcstatus_test)

set (SOURCE_FILES
    "./src/main.cpp"
)

# [Boost]
find_package(Boost 1.59 COMPONENTS system REQUIRED)
if(${Boost_FOUND})
    message(${Boost_INCLUDE_DIRS})
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIR})
endif()
# [Boost end]

add_subdirectory("../" "../bin")
include_directories("../include")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(mcstatus_test ${SOURCE_FILES})
target_link_libraries(mcstatus_test mcstatus)
