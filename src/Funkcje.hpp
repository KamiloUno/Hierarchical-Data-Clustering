#ifndef Funkcje
#define Funkcje
/**
* @file
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>
/**
* Wyswietla pomoc w konsoli, informujac uzytkownika o poprawnym uzyciu programu.
*/
void help();
/**
* Funkcja sprawdzajaca poprawnosc i wczytujaca parametry wejsciowe z linii polecen.
* @param argc liczba argumentow
* @param argv parametry
* @param wejscie nazwa pliku wejsciowego
* @param wyjscie nazwa pliku wyjsciowego
* @param k parametr algorytmu oznaczajacy liczbe grup
* @return 1 jezeli parametry podano poprawnie
* @return 0 jezeli parametry podano niepoprawnie
*/
bool czyt_param(int argc, char** argv, std::string& wejscie, std::string& wyjscie, int& k);
/**
* Wczytuje dane z pliku wejsciowego i zapisuje je do wektora wektorow (Wektory).
* @param wejscie nazwa pliku wejsciowego
* @param Wektory referencja na wektor wektorow, do którego wczytywane s¹ dane
*/
void odczyt(std::string wejscie, std::vector<std::vector<double>>& Wektory);
/**
* Struktura reprezentujaca grupe punktow. Zawiera wektor indeksow punktow w danej grupie.
*/
struct Grupa {
    std::vector<int> punkty;
};
/**
* Oblicza odleglosc euklidesowa miedzy dwoma punktami.
* @param punkt1 wektor reprezentujacy pierwszy punkt w przestrzeni
* @param punkt2 wektor reprezentujacy drugi punkt w przestrzeni
* @return odleglosc euklidesowa miedzy punktami
*/
double obliczOdleglosc(const std::vector<double>& punkt1, const std::vector<double>& punkt2);
/**
* Tworzy i zwraca macierz odleglosci miedzy punktami na podstawie wektora punktow.
* @param wektory wektor wektorow reprezentujacych punkty w przestrzeni
* @return macierz odleglosci miedzy punktami
*/
std::vector<std::vector<double>> MatrixOdl(const std::vector<std::vector<double>>& wektory);
/**
* Funkcja grupuje punkty w k grup za pomoca algorytmu hierarchicznego.
* @param wektory wektor wektorow reprezentuj¹cych punkty w przestrzeni
* @param k liczba grup do uzyskania
* @return wektor struktur Grupa reprezentujacych ostateczne grupy punktow
*/
std::vector<Grupa> grupowanie(const std::vector<std::vector<double>>& wektory, int k);
/**
* Zapisuje indeksy punktow w grupach do pliku wyjsciowego.
* @param grupy wektor struktur Grupa, reprezentujacych grupy punktow
* @param wyjscie nazwa pliku wyjsciowego
*/
void zapiszIndeks(const std::vector<Grupa>& grupy, const std::string& wyjscie);

#endif
