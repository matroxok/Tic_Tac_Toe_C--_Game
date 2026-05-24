# Kółko i krzyżyk

Konsolowa gra w kółko i krzyżyk napisana w C++. Program pozwala wybrać rozmiar planszy oraz liczbę znaków w rzędzie potrzebną do wygranej. Po zakończeniu partii można uruchomić nową grę albo wyjść z aplikacji.

## Wymagania

- CMake 3.10 lub nowszy
- Kompilator C++

## Windows

w katalogu projektu:

```powershell
cmake -S . -B build
cmake --build build
.\build\Debug\KolkoIKrzyzyk.exe
```

albo

```powershell
.\build\Release\KolkoIKrzyzyk.exe
```

## macOS / linux

```bash
brew install cmake
```

w katalogu projektu:

```bash
cmake -S . -B build
cmake --build build
./build/KolkoIKrzyzyk
```

## Jak grać

Po uruchomieniu program zapyta o:

- rozmiar planszy
- liczbę znaków w rzędzie potrzebną do wygranej

Ruch wpisuje się jako numer wiersza i kolumny, np.:

```text
1 2
```

Po zakończeniu gry można wybrać:

```text
1 - Nowa gra
2 - Wyjście
```
