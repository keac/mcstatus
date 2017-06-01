cmake_minimum_required (VERSION 2.8)
project (mcstatus)

set(PROJECT_SOURCE_DIR "./src")
set(PROJECT_INCLUDE_DIR "./include")
include_directories(${PROJECT_INCLUDE_DIR})

set (SOURCE_FILES
    "${PROJECT_SOURCE_DIR}/domain.cpp"
    "${PROJECT_SOURCE_DIR}/color.cpp"
    "${PROJECT_SOURCE_DIR}/packet.cpp"
    "${PROJECT_SOURCE_DIR}/mcstatus.cpp"
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# [Boost]
find_package(Boost 1.59 COMPONENTS system REQUIRED)
if(${Boost_FOUND})
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIR})
endif()
# [Boost end]

add_library(mcstatus SHARED ${SOURCE_FILES})

# linking boost
target_link_libraries(mcstatus ${Boost_LIBRARIES})
# fix raspberry pi
target_link_libraries(mcstatus -lpthread -lm)

# Install
install (TARGETS mcstatus LIBRARY DESTINATION lib)
install (DIRECTORY ${PROJECT_INCLUDE_DIR} DESTINATION include)
