cmake_minimum_required(VERSION 3.5)

list(APPEND EXTRA_COMPONENT_DIRS "./libs")
list(APPEND EXTRA_COMPONENT_DIRS "./include")
list(APPEND EXTRA_COMPONENT_DIRS "./src")

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(thermal)
