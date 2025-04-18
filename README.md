# Simple Gravity Simulation

## Opis

Projekt symuluje działanie grawitacji w przestrzeni dwuwymiarowej. Do reprezentacji graficznej używa biblioteki **SFML** w wersji 2.5.1.  

## Wymagania

- System operacyjny: Linux
- Kompilator: `g++`
- Dodatkowe zależności:
  - `SFML` (>= 2.5.1)
  - `make` (opcjonalnie, jeśli korzystasz z Makefile)

## Instalacja

```sh
git clone https://github.com/DexonRax/simple-gravity-simulation.git
cd simple-gravity-simulation
make
```

## Użycie Makefile
- make – kompiluje projekt
- make run – kompiluje (jeśli potrzeba) i uruchamia symulację
- make clean – usuwa pliki wynikowe (*.o, binarkę)

## Sterowanie
- W / A / S / D – poruszanie kamerą
- F1 – przybliżanie kamery
- F2 – oddalanie kamery
- F3 – przyspieszanie czasu symulacji
- F4 – spowalnianie czasu symulacji
- Prawy przycisk myszy – przełączanie się na następną planetę
- Lewy przycisk myszy – przełączanie się na poprzednią planetę