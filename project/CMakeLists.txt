cmake_minimum_required(VERSION 3.10)

project(WorkProject)

FIND_PACKAGE(Boost COMPONENTS program_options REQUIRED )

add_executable(WorkProject project.cpp)

target_link_libraries(WorkProject PRIVATE Boost::program_options)