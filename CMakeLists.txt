cmake_minimum_required(VERSION 3.8.0)

include(cmake/warnings.cmake)

message(STATUS "Setting build type to 'RelWithDebInfo' as none was specified.")
set(CMAKE_BUILD_TYPE
    RelWithDebInfo
    CACHE STRING "Choose the type of build." FORCE)
# Set the possible values of build type for cmake-gui, ccmake
set_property(
    CACHE CMAKE_BUILD_TYPE
    PROPERTY STRINGS
        "Debug"
        "Release"
        "MinSizeRel"
        "RelWithDebInfo"
)

project(rndpsw VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(fmt)

find_package(fmt)
find_package(Boost COMPONENTS program_options REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} 
                        PRIVATE ${Boost_LIBRARIES}
                        PRIVATE fmt::fmt)