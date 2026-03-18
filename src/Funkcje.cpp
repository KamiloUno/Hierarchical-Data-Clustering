#include "Funkcje.hpp"

void help() { //Wyswietla pomoc w konsoli, informujac uzytkownika o poprawnym uzyciu programu.
    std::cout << "\nAby uzyc programu - kolejnosc podanych parametrow jest obojetna, ale ich obecnosc obowiazkowa: \n";
    std::cout << "'HierarchicalClustering.exe' -i 'wejscie.txt' -o 'wyjscie.txt' -k 'liczba naturalna' \n";
}

bool czyt_param(int argc, char** argv, std::string& wejscie, std::string& wyjscie, int& k) { //Funkcja sprawdzajaca poprawnosc i wczytujaca parametry wejsciowe z linii polecen
    bool sprawdz1 = false;
    bool sprawdz2 = false;
    bool sprawdz3 = false;

    k = 0;

    if (argc != 7) {
        return false;
    }

    for (int i = 0; i < argc - 1; i++) {
        std::string param(argv[i]);
        if (param == "-i") {
            std::string nastepny_param(argv[i + 1]);
            wejscie = nastepny_param;
            std::cout << "Wejscie: " << wejscie << "\n";
            sprawdz1 = true;
        }
        else if (param == "-o") {
            std::string nastepny_param(argv[i + 1]);
            wyjscie = nastepny_param;
            std::cout << "Wyjscie: " << wyjscie << "\n";
            sprawdz2 = true;
        }
        else if (param == "-k") {
            k = atoi(argv[i + 1]);
            std::cout << "K: " << k << "\n";
            sprawdz3 = true;
        }
    }

    if (sprawdz1 == false || sprawdz2 == false || sprawdz3 == false) {
        std::cout << "\nPodano niepoprawny parametr \n";
        return false;
    }

    return true;
}

void odczyt(std::string wejscie, std::vector<std::vector<double>>& Wektory) { //Wczytuje dane z pliku wejœciowego i zapisuje je do wektora wektorów (Wektory)
    std::ifstream dane(wejscie);
    if (dane.is_open()) {
        std::string line;
        int N;
        int D;

        if (std::getline(dane, line)) {
            std::istringstream iss(line);
            if (!(iss >> N)) {
                std::cout << "Blad: Nie mo¿na odczytac liczby punktow danych." << std::endl;
                return;
            }
            std::cout << "Liczba punktow danych N: " << N << std::endl;
        }

        if (std::getline(dane, line)) {
            std::istringstream iss(line);
            if (!(iss >> D)) {
                std::cout << "Blad: Nie mo¿na odczytac liczby wymiarow" << std::endl;
                return;
            }
            std::cout << "Liczba wymiarow D: " << D << std::endl;
        }

        std::getline(dane, line);

        for (int i = 0; i < N; i++) {
            if (std::getline(dane, line)) {
                std::istringstream iss(line);

                std::vector<double> AktWektor(D);

                for (int j = 0; j < D; ++j) {
                    if (!(iss >> AktWektor[j])) {
                        std::cerr << "B³¹d podczas odczytu danych z wiersza." << std::endl;
                        return;
                    }
                }

                Wektory.push_back(AktWektor);
            }
        }

        std::cout << "----------------------------------------" << std::endl;
        for (size_t i = 0; i < Wektory.size(); ++i) {
            std::cout << "Punkt" << i + 1 << ": ";
            for (const double& value : Wektory[i]) {
                std::cout << value << " ";
            }
            std::cout << std::endl;
        }
        dane.close();
    }
    else {
        std::cerr << "Nie udalo sie otworzyc pliku wejsciowego";
    }
}

double obliczOdleglosc(const std::vector<double>& punkt1, const std::vector<double>& punkt2) { //Oblicza odleg³oœæ euklidesow¹ miêdzy dwoma punktami
    double odleglosc = 0.0;
    for (size_t i = 0; i < punkt1.size(); ++i) {
        odleglosc += std::pow(punkt1[i] - punkt2[i], 2);
    }
    return std::sqrt(odleglosc);
}

std::vector<std::vector<double>> MatrixOdl(const std::vector<std::vector<double>>& wektory) { //Tworzy i zwraca macierz odleg³oœci miêdzy punktami na podstawie wektora punktów
    int N = wektory.size();
    std::vector<std::vector<double>> odlM(N, std::vector<double>(N, 0.0));

    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            double distance = obliczOdleglosc(wektory[i], wektory[j]);
            odlM[i][j] = odlM[j][i] = distance;
        }
    }

    return odlM;
}

std::vector<Grupa> grupowanie(const std::vector<std::vector<double>>& wektory, int k) { //Grupuje punkty w k grup za pomoc¹ algorytmu hierarchicznego klastrowania
    // Zwraca wektor grup, gdzie ka¿da grupa zawiera indeksy punktów w danej grupie
    int N = wektory.size();

    // Inicjalizacja grup dla ka¿dego punktu
    std::vector<Grupa> grupki(N);
    for (int i = 0; i < N; ++i) {
        grupki[i].punkty.push_back(i);
    }

    while (grupki.size() > k) {
        // ZnajdŸ najbli¿sze grupy
        int minI = 0, minJ = 1;
        double minDistance = obliczOdleglosc(wektory[grupki[0].punkty[0]], wektory[grupki[1].punkty[0]]);

        for (size_t i = 0; i < grupki.size(); ++i) {
            for (size_t j = i + 1; j < grupki.size(); ++j) {
                double distance = obliczOdleglosc(wektory[grupki[i].punkty[0]], wektory[grupki[j].punkty[0]]);
                if (distance < minDistance) {
                    minDistance = distance;
                    minI = i;
                    minJ = j;
                }
            }
        }

        // Po³¹cz najbli¿sze grupy
        grupki[minI].punkty.insert(grupki[minI].punkty.end(), grupki[minJ].punkty.begin(), grupki[minJ].punkty.end());
        grupki.erase(grupki.begin() + minJ);
    }

    return grupki;
}

void zapiszIndeks(const std::vector<Grupa>& grupy, const std::string& wyjscie) { //Zapisuje indeksy punktów w grupach do pliku wyjsciowego
    std::ofstream output(wyjscie);
    if (output.is_open()) {
        std::vector<std::pair<int, int>> punktyZgrupa;  // Para (nr punktu, indeks grupy punktu)

        // Zbierz punkty z ich indeksami grup
        for (size_t IdxGrupy = 0; IdxGrupy < grupy.size(); ++IdxGrupy) {
            for (size_t IdxPunktu : grupy[IdxGrupy].punkty) {
                punktyZgrupa.push_back(std::make_pair(IdxPunktu + 1, IdxGrupy + 1));
            }
        }

        // Posortuj punkty rosn¹co
        std::sort(punktyZgrupa.begin(), punktyZgrupa.end(), [](const auto& a, const auto& b) {
            return a.first < b.first;
            });

        // Zamieñ miejscami numer punktu z indeksem grupy w posortowanym zestawie
        for (const auto& punktZGr : punktyZgrupa) {
            output << punktZGr.second << " % indeks grupy punktu " << punktZGr.first << std::endl;
        }

        output.close();
        std::cout << "Zapisano do pliku: " << wyjscie << std::endl;
    }
    else {
        std::cerr << "Nie udalo sie otworzyc pliku wyjsciowego" << std::endl;
    }
}


