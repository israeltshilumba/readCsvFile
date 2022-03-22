cmake_minimum_required(VERSION 3.20)
project(readCsvFile)

set(CMAKE_CXX_STANDARD 14)

add_executable(readCsvFile main.cpp cmake-build-debug/classes/Aktie.cpp cmake-build-debug/classes/Aktie.h cmake-build-debug/classes/HashNode.cpp cmake-build-debug/classes/HashNode.h cmake-build-debug/classes/Hashtable.cpp cmake-build-debug/classes/Hashtable.h)
