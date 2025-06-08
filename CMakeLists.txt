cmake_minimum_required(VERSION 3.10)
project(KolkoIKrzyzyk)

set(CMAKE_CXX_STANDARD 17)

# Ścieżka do SFML — katalog główny (gdzie są foldery include, lib, bin)
# set(SFML_DIR "C:/SFML-2.6.2")
set(CMAKE_PREFIX_PATH "C:/msys64/ucrt64")


# Znajdź SFML
set(CMAKE_PREFIX_PATH "${SFML_DIR}")
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Ścieżki nagłówków
include_directories(include)

# Pliki źródłowe
# file(GLOB SOURCES "src/*.cpp")
set(SOURCES
    src/gui.cpp
    src/ai.cpp
    src/board.cpp
    src/game.cpp
)

# Tworzymy plik wykonywalny
add_executable(KolkoIKrzyzyk ${SOURCES})

# Linkujemy z bibliotekami SFML
target_link_libraries(KolkoIKrzyzyk sfml-graphics sfml-window sfml-system)
