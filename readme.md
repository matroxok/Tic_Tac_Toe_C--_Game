### Instrukcja uruchamiania

Najprosciej odpalic gotowy plik `.exe` z folderu `build`:

```powershell
cd build
.\KolkoIKrzyzyk.exe
```

Mozesz tez uruchomic go bez zmiany katalogu:

```powershell
.\build\KolkoIKrzyzyk.exe
```

Jesli zmieniasz kod, przebuduj projekt:

```powershell
cmake --build build
```

Wymagania do pelnego builda:

- MinGW GCC compiler
- CMake
- SFML
- MSYS2

Pliki `.dll` i czcionki potrzebne do uruchomienia sa skopiowane do folderu `build`.
