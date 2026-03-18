#include <iostream>
#include <vector>
#include "Funkcje.hpp"

int main(int argc, char** argv) { //Główna funkcja programu
    std::string wejscie;
    std::string wyjscie;
    int k = 0;

    if (czyt_param(argc, argv, wejscie, wyjscie, k) == false) {
        help();
        return 1;
    }

    std::vector<std::vector<double>> wektory;
    odczyt(wejscie, wektory);

    std::vector<std::vector<double>> macierzodleglosci = MatrixOdl(wektory);
    std::vector<Grupa> grupy = grupowanie(macierzodleglosci, k);

    zapiszIndeks(grupy, wyjscie);

    return 0;
}
