cmake_minimum_required(VERSION 3.5) # CMake install : https://cmake.org/download/
project(backuper LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "D:/programs/Qt/5.15.2/mingw81_64") # Qt Kit Dir
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt5 COMPONENTS Widgets REQUIRED) # Qt COMPONENTS
aux_source_directory(./src srcs)

# boost filesystem
# set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH}")
# list(APPEND CMAKE_PREFIX_PATH "")
set(BOOST_ROOT "D:/programs/boost_1_82_0_mingw_8_1_0") # 设置boost库搜索路径
set(Boost_NO_SYSTEM_PATHS ON) # 只搜索上语句设置的搜索路径
find_package(Boost COMPONENTS filesystem REQUIRED)
message("boost include dir" ${Boost_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})  # Boost_INCLUDE_DIRS

# Specify MSVC UTF-8 encoding   
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_executable(${PROJECT_NAME}
    WIN32 # If you need a terminal for debug, please comment this statement 
    ${srcs} 
) 
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets) # Qt5 Shared Library
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::filesystem)

# get_cmake_property(_variableNames VARIABLES)
# foreach (_variableName ${_variableNames})
#     message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()