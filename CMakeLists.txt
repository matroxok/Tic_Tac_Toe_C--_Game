cmake_minimum_required(VERSION 3.10)
project(KolkoIKrzyzyk)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    add_compile_options(/utf-8)
endif()

# Dodaj katalog nagłówków
include_directories(include)

# Wyszukaj wszystkie pliki źródłowe
file(GLOB SOURCES "src/*.cpp")

# Tworzymy plik wykonywalny
add_executable(KolkoIKrzyzyk ${SOURCES})
