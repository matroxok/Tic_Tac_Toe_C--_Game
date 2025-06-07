cmake_minimum_required(VERSION 3.10)
project(KolkoIKrzyzyk)

set(CMAKE_CXX_STANDARD 17)

# Dodaj katalog nagłówków
include_directories(include)

# Wyszukaj wszystkie pliki źródłowe
file(GLOB SOURCES "src/*.cpp")

# Tworzymy plik wykonywalny
add_executable(KolkoIKrzyzyk ${SOURCES})
