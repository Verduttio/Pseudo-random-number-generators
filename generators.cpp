#include <iostream>
#include <cmath>
#include <fstream> // do zapisu danych do pliku

using namespace std;

//generatory--start
unsigned int generatorLiczbyLosowej(long long& x_i, long long m, int a, int c) {
    x_i = (a * x_i + c)%m;
    return x_i;
}

double generatorLiczbyLosowejOd0Do1(long long& x_i, long long m, int a, int c){
    x_i = (a * x_i + c)%m;
    return x_i / (double)m;
}

int generatorLiczbyLosowejRozkladBernoulliego(long long& x_i, long long m, int a, int c, double p) {
    x_i = (a * x_i + c)%m;
    double liczbaLosowa = x_i/(double)m;
    // P{X = 0} = 1 - p
    // P{X = 1} = p

    return liczbaLosowa < p ? 1 : 0;
}

long long generatorLiczbyLosowejRozkladDwumianowy(long long& x_i, long long m, int a, int c, double p, int n) {
    long long suma = 0;
    for(int i = 0; i < n; i++) {
        x_i = (a * x_i + c)%m;
        double liczbaLosowaOd0Do1 = x_i/(double)m;
        if(liczbaLosowaOd0Do1 < p) suma++;
    }
    return suma;
}

long double silnia(int i) {
    long double result = 1;
    for(int j = 2; j <= i; j++)
        result *= j;
    return result;
}

int generatorLiczbyLosowejRozkladPoisson(double & x_i, long long m, int a, int c, double lambda) {
    x_i = ((long long)(a * x_i + c)%m);

    double Un = x_i/(double)m;
    double sum = 0;
    int i = -1;
    do {
        i++;
        sum += (exp(-lambda)*pow(lambda, i))/silnia(i);
    } while(Un > sum);
    return i;
}

double generatorLiczbyLosowejRozkladWykladniczy(double& x_i, long long m, int a, int c, double lambda) {
    x_i = ((long long)(a * x_i + c)%m);
    double Un = x_i/(double)m;

    return (-1/lambda)*log(1-Un);
}

double generatorLiczbyLosowejRozkladNormalny(double& x_i, long long m, int a, int c, double sigma, double mi) {
    // x_i należy do [0, 1)
    x_i = ((long long)(a * x_i + c)%m);
    double U1 = 1-(x_i/(double)m);
    x_i = ((long long)(a * x_i + c)%m);
    double U2 = 1-(x_i/(double)m);
    // teraz U należy do (0, 1]


    long double RDoKwadratu = -2*log(U1);
    long double theta = 2*M_PI*U2;

    double Z1 = sqrt(RDoKwadratu)*cos(theta);
    double Z2 = sqrt(RDoKwadratu)*sin(theta);

    return Z1*sigma + mi;
}
//generatory --end


// generowanie plików
void liczbyDoPliku_GeneratorG(int liczbaDanych) {
    fstream plik;
    plik.open("generatorG.txt", ios::out);
    if(!plik.good()) cout << "Blad z otwarciem pliku\n";

    plik.precision(15);

    // początkowa inicjalizacja --start
    long long x_i = 3;
    long long m = pow(2, 32);  // 2^32
    int a = 22695477;
    int c = 1;
    // początkowa inicjalizacja --koniec

    //zapisanie minimalnej i maksymalnej liczby
    plik << 0 << endl;
    plik << m-1 << endl;

    //zapisanie liczby danych
    plik << liczbaDanych << endl;

    //wpisanie wylosowanych liczb
    for(int i = 0; i < liczbaDanych; i++) {
        plik << generatorLiczbyLosowej(x_i, m, a, c) << endl;
    }

    plik.close();
}

void liczbyDoPliku_GeneratorJ(int liczbaDanych) {
    fstream plik;
    plik.open("generatorJ.txt", ios::out);
    if(!plik.good()) cout << "Blad z otwarciem pliku\n";

    plik.precision(15);

    // początkowa inicjalizacja --start
    long long x_i = 3;
    long long m = pow(2, 32);  // 2^32
    int a = 22695477;
    int c = 1;
    // początkowa inicjalizacja --koniec

    //zapisanie najmniejszej i najwiekszej liczby (przedzialu)
    plik << 0 << endl;
    plik << 1 << endl;

    //zapisanie liczby danych
    plik << liczbaDanych << endl;

    //wpisanie wylosowanych liczb
    for(int i = 0; i < liczbaDanych; i++) {
        plik << generatorLiczbyLosowejOd0Do1(x_i, m, a, c) << endl;
    }

    plik.close();
}

void liczbyDoPliku_GeneratorB(int liczbaDanych, double p) {
    fstream plik;
    plik.open("generatorB.txt", ios::out);
    if(!plik.good()) cout << "Blad z otwarciem pliku\n";

    plik.precision(15);

    // początkowa inicjalizacja --start
    long long x_i = 2;
    long long m = pow(2, 32);  // 2^32
    int a = 22695477;
    int c = 1;
    // początkowa inicjalizacja --koniec

    //zapisanie prawdopodbienstwa
    plik << p << endl;

    //zapisanie liczby danych
    plik << liczbaDanych << endl;

    for(int i = 0; i < liczbaDanych; i++) {
        plik << generatorLiczbyLosowejRozkladBernoulliego(x_i, m, a, c, p) << endl;
    }

    plik.close();
}

void liczbyDoPliku_GeneratorD(int liczbaDanych, int n, double p) {
    fstream plik;
    plik.open("generatorD.txt", ios::out);
    if(!plik.good()) cout << "Blad z otwarciem pliku\n";

    plik.precision(15);

    // początkowa inicjalizacja --start
    long long x_i = 3;
    long long m = pow(2, 32);  // 2^32
    int a = 22695477;
    int c = 1;
    // początkowa inicjalizacja --koniec

    //zapisanie n oraz p
    plik << n << endl;
    plik << p << endl;

    //zapisanie liczby danych
    plik << liczbaDanych << endl;

    for(int i = 0; i < liczbaDanych; i++) {
        plik << generatorLiczbyLosowejRozkladDwumianowy(x_i, m, a, c, p, n) << endl;
    }

    plik.close();
}

void liczbyDoPliku_GeneratorP(int liczbaDanych, int lambda) {
    fstream plik;
    plik.open("generatorP.txt", ios::out);
    if(!plik.good()) cout << "Blad z otwarciem pliku\n";

    plik.precision(15);

    // początkowa inicjalizacja --start
    double x_i = 13;
    long long m = pow(2, 32);  // 2^32
    int a = 22695477;
    int c = 1;
    // początkowa inicjalizacja --koniec

    //zapisanie lambdy
    plik << lambda << endl;

    //zapisanie liczby danych
    plik << liczbaDanych << endl;

    for(int i = 0; i < liczbaDanych; i++) {
        plik << generatorLiczbyLosowejRozkladPoisson(x_i, m, a, c, lambda) << endl;
    }

    plik.close();

}

void liczbyDoPliku_GeneratorW(int liczbaDanych, int lambda ) {
    fstream plik;
    plik.open("generatorW.txt", ios::out);
    if(!plik.good()) cout << "Blad z otwarciem pliku\n";

    plik.precision(15);

    // początkowa inicjalizacja --start
    double x_i = 13;
    long long m = pow(2, 32);  // 2^32
    int a = 22695477;
    int c = 1;
    // początkowa inicjalizacja --koniec

    //zapisanie lambdy
    plik << lambda << endl;

    //zapisanie liczby danych
    plik << liczbaDanych << endl;

    for(int i = 0; i < liczbaDanych; i++) {
        plik << generatorLiczbyLosowejRozkladWykladniczy(x_i, m, a, c, lambda) << endl;
    }

    plik.close();

}

void liczbyDoPliku_GeneratorN(int liczbaDanych, double sigma, double mi) {
    fstream plik;
    plik.open("generatorN.txt", ios::out);
    if(!plik.good()) cout << "Blad z otwarciem pliku\n";

    plik.precision(15);

    // początkowa inicjalizacja --start
    double x_i = 3;
    long long m = pow(2, 32);  // 2^32
    int a = 22695477;
    int c = 1;
    // początkowa inicjalizacja --koniec

    //zapisanie sigmy oraz mi
    plik << sigma << endl;
    plik << mi << endl;

    //zapisanie liczby danych
    plik << liczbaDanych << endl;

    for(int i = 0; i < liczbaDanych; i++) {
        plik << generatorLiczbyLosowejRozkladNormalny(x_i, m, a, c, sigma, mi) << endl;
    }

    plik.close();
}

int main() {
   liczbyDoPliku_GeneratorN(1000, 4, 3);

    return 0;
}
