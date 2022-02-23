#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>


using namespace std;

long double silnia(int i) {
    long double result = 1;
    for(int j = 2; j <= i; j++)
        result *= j;
    return result;
}

long double dwumianNewtona(int n, int k) {
    return silnia(n)/(silnia(k)*silnia(n-k));
}

unsigned int policzWystapieniaWPrzedziale(const double* dane, int rozmiarDanych, double poczatekPrzedzialu, double koniecPrzedzialu ) {
    unsigned int wystapienia = 0;
    for(int i = 0; i < rozmiarDanych; i++) {
        if(dane[i] >=poczatekPrzedzialu && dane[i] < koniecPrzedzialu)
            wystapienia++;
    }
    return wystapienia;
}

double chiKwadratGeneratorG() {
    cout.precision(15);

    fstream dane;
    dane.open("generatorG.txt", ios::in);
    if(!dane.good()) cout << "Blad z otwarciem pliku\n";

    int liczbaDanych;
    double minNumber;
    double maxNumber;
    dane >> minNumber >> maxNumber;
    dane >> liczbaDanych;

    cout << "minNumber: " << minNumber << endl;
    cout << "maxNumber: " << maxNumber << endl;
    cout << "liczbaDanych: " << liczbaDanych << endl;

    auto* daneTablica = new double [liczbaDanych];

    for(int i = 0; i < liczbaDanych; i++) {
        dane >> daneTablica [ i ];
    }

 /*   // wyswietlanie danych
    for(int i = 0; i < liczbaDanych; i++) {
        cout << daneTablica[i] << endl;
    }*/

    // bedziemy mieli 10 przedzialow
    int liczbaCech = 10;
    double tabelaChi [liczbaCech] [6];
    // [poczatekPrzedzialu] [koniec przedzialu] [observed] [expected] [(obs-exp)^2] [component (obs-exp)^2/exp]
    //              0               1               2           3           4           5
    // inicjalizacja
    double skokPrzedzialu = (maxNumber-minNumber)/(double)liczbaCech;
    cout << "skok przedzialu: " << skokPrzedzialu << endl;
    tabelaChi[0][0] = minNumber;
    tabelaChi[0][1] = minNumber+skokPrzedzialu;
    for (int i = 1; i < liczbaCech; i++) {
        tabelaChi[i][0] = minNumber+skokPrzedzialu;
        minNumber += skokPrzedzialu;
        tabelaChi[i][1] = minNumber+skokPrzedzialu;
    }

    //liczenie wystapien [observed]
    for(int i = 0; i < liczbaCech; i++) {
        tabelaChi[i][2] = policzWystapieniaWPrzedziale(daneTablica, liczbaDanych, tabelaChi[i][0], tabelaChi[i][1]);
    }

    //liczenie wartosci spodziewanej [3]
    for(int i = 0; i < liczbaCech; i++) {
        tabelaChi[i][3] = liczbaDanych*1/liczbaCech;
    }

    //liczenie [(obs-exp)^2] [4]
    for(int i = 0; i < liczbaCech; i++) {
        tabelaChi[i][4] = (tabelaChi[i][2]-tabelaChi[i][3])*(tabelaChi[i][2]-tabelaChi[i][3]);
    }

    //liczenie component [5]
    for(int i = 0; i < liczbaCech; i++) {
        tabelaChi[i][5] = tabelaChi[i][4]/tabelaChi[i][3];
    }

    //wyliczenie wartosci empirycznej
    double wartoscEmpiryczna = 0;
    for (int i =0; i < liczbaCech; i++) {
        wartoscEmpiryczna += tabelaChi[i][5];
    }

    //wyswietlanie kontrolne liczby wystapien
    cout << "[wartosc]                      [observed] [expected] [(obs-exp)^2] [(obs-exp)^2/exp]" << endl;
    for(int i = 0; i < liczbaCech; i++) {
        printf("[%llf, %llf] | %llf | %llf | %llf | %llf \n",
               tabelaChi[i][0], tabelaChi[i][1], tabelaChi[i][2], tabelaChi[i][3],
               tabelaChi[i][4], tabelaChi[i][5]);
    }

    cout << "wartoscEmpiryczna: " << wartoscEmpiryczna << endl;

    delete [] daneTablica;

    return wartoscEmpiryczna;
}

double chiKwadratGeneratorJ() {
    cout.precision(15);

    fstream dane;
    dane.open("generatorJ.txt", ios::in);
    if(!dane.good()) cout << "Blad z otwarciem pliku\n";

    int liczbaDanych;
    double minNumber;
    double maxNumber;
    dane >> minNumber >> maxNumber;
    dane >> liczbaDanych;

    cout << "minNumber: " << minNumber << endl;
    cout << "maxNumber: " << maxNumber << endl;
    cout << "liczbaDanych: " << liczbaDanych << endl;

    auto* daneTablica = new double [liczbaDanych];

    for(int i = 0; i < liczbaDanych; i++) {
        dane >> daneTablica [ i ];
    }

    /*// wyswietlanie danych
    for(int i = 0; i < liczbaDanych; i++) {
        cout << daneTablica[i] << endl;
    }*/

    // bedziemy mieli 10 stopni wolnosci
    int liczbaCech = 10;
    double tabelaChi [liczbaCech] [6];
    // [poczatekPrzedzialu] [koniec przedzialu] [observed] [expected] [(obs-exp)^2] [component (obs-exp)^2/exp]
    //              0               1               2           3           4           5
    // inicjalizacja
    double skokPrzedzialu = (maxNumber-minNumber)/(double)liczbaCech;
    cout << "skok przedzialu: " << skokPrzedzialu << endl;
    tabelaChi[0][0] = minNumber;
    tabelaChi[0][1] = minNumber+skokPrzedzialu;
    for (int i = 1; i < liczbaCech; i++) {
        tabelaChi[i][0] = minNumber+skokPrzedzialu;
        minNumber += skokPrzedzialu;
        tabelaChi[i][1] = minNumber+skokPrzedzialu;
    }

    //liczenie wystapien [observed]
    for(int i = 0; i < liczbaCech; i++) {
        tabelaChi[i][2] = policzWystapieniaWPrzedziale(daneTablica, liczbaDanych, tabelaChi[i][0], tabelaChi[i][1]);
    }

    //liczenie wartosci spodziewanej [3]
    for(int i = 0; i < liczbaCech; i++) {
        tabelaChi[i][3] = liczbaDanych*1/liczbaCech;
    }

    //liczenie [(obs-exp)^2] [4]
    for(int i = 0; i < liczbaCech; i++) {
        tabelaChi[i][4] = (tabelaChi[i][2]-tabelaChi[i][3])*(tabelaChi[i][2]-tabelaChi[i][3]);
    }

    //liczenie component [5]
    for(int i = 0; i < liczbaCech; i++) {
        tabelaChi[i][5] = tabelaChi[i][4]/tabelaChi[i][3];
    }

    //wyliczenie wartosci empirycznej
    double wartoscEmpiryczna = 0;
    for (int i =0; i < liczbaCech; i++) {
        wartoscEmpiryczna += tabelaChi[i][5];
    }

    cout << "[wartosc]              [observed] [expected] [(obs-exp)^2] [(obs-exp)^2/exp]" << endl;
    for(int i = 0; i < liczbaCech; i++) {
        printf("[%llf, %llf] | %llf | %llf | %llf | %llf \n",
               tabelaChi[i][0], tabelaChi[i][1], tabelaChi[i][2], tabelaChi[i][3],
               tabelaChi[i][4], tabelaChi[i][5]);
    }

    cout << "wartoscEmpiryczna: " << wartoscEmpiryczna << endl;

    delete [] daneTablica;

    return wartoscEmpiryczna;
}

double policzWystapieniaGeneratorB(const double* dane, int rozmiarDanych, int wartosc ) {
    int wystapienia = 0;
    for(int i = 0; i < rozmiarDanych; i++) {
        if(dane[i] == wartosc)
            wystapienia++;
    }
    return wystapienia;
}

double chiKwadratGeneratorB() {
    cout.precision(15);

    fstream dane;
    dane.open("generatorB.txt", ios::in);
    if(!dane.good()) cout << "Blad z otwarciem pliku\n";

    double p;
    double minNumber;
    double maxNumber;
    int liczbaDanych;

    dane >> p;
    dane >> liczbaDanych;

    cout << "p: " << p << endl;
    cout << "liczbaDanych: " << liczbaDanych << endl;

    auto* daneTablica = new double [liczbaDanych];

    for(int i = 0; i < liczbaDanych; i++) {
        dane >> daneTablica [ i ];
    }

   /* // wyswietlanie danych
    for(int i = 0; i < liczbaDanych; i++) {
        cout << daneTablica[i] << endl;
    }*/

    // bedziemy mieli 2 wartosci liczbowe
    int liczbaCech = 2;
    double tabelaChi [liczbaCech] [5];
    // [wartosc] [observed] [expected] [(obs-exp)^2] [component (obs-exp)^2/exp]
    //     0        1          2           3                    4
    // inicjalizacja
    tabelaChi[0][0] = 0;
    tabelaChi[1][0] = 1;

    //liczenie wystapien [observed]
    for(int i = 0; i < liczbaCech; i++) {
        tabelaChi[i][1] = policzWystapieniaGeneratorB(daneTablica, liczbaDanych, tabelaChi[i][0]);
    }

    //liczenie wartosci spodziewanej [2]
    tabelaChi[0][2] = liczbaDanych*(1-p);
    tabelaChi[1][2] = liczbaDanych*(p);

    //liczenie [(obs-exp)^2] [3]
    for(int i = 0; i < liczbaCech; i++) {
        tabelaChi[i][3] = (tabelaChi[i][1]-tabelaChi[i][2])*(tabelaChi[i][1]-tabelaChi[i][2]);
    }

    //liczenie component [4]
    for(int i = 0; i < liczbaCech; i++) {
        tabelaChi[i][4] = tabelaChi[i][3]/tabelaChi[i][2];
    }

    //wyliczenie wartosci empirycznej
    double wartoscEmpiryczna = 0;
    for (int i =0; i < liczbaCech; i++) {
        wartoscEmpiryczna += tabelaChi[i][4];
    }

    cout << "[wartosc] [observed] [expected] [(obs-exp)^2] [(obs-exp)^2/exp]" << endl;
    for(int i = 0; i < liczbaCech; i++) {
        printf("[%llf] | %llf | %llf | %llf | %llf \n",
               tabelaChi[i][0], tabelaChi[i][1], tabelaChi[i][2], tabelaChi[i][3],
               tabelaChi[i][4]);
    }

    cout << "wartoscEmpiryczna: " << wartoscEmpiryczna << endl;

    delete [] daneTablica;

    return wartoscEmpiryczna;
}

vector<int> zwrocUnikalneLiczby(const unsigned int* dane, int rozmiarDanych) {
    vector<int> wynik;
    for (int i = 0; i < rozmiarDanych; i++) {
        bool dopisz = true;
        for (int j = 0; j < i; j++) {
            if (dane[i] == dane[j]) {
                dopisz = false;
                break;
            }
        }
        if (dopisz) {
            wynik.push_back(dane[i]);
        }
    }
    return wynik;
}

void policzWystapienia(const unsigned int* dane, const int liczbaDanych, double tabelaChi[][5], const int liczbaStopni) {
    for(int i = 0; i < liczbaStopni; i++) {
        double wystapienia = 0;
        for(int j = 0; j < liczbaDanych; j++) {
            if(tabelaChi[i][0] == dane[j]) wystapienia++;
        }
        tabelaChi[i][1] = wystapienia;
    }
}

double chiKwadratGeneratorD() {
    cout.precision(15);

    fstream dane;
    dane.open("generatorD.txt", ios::in);
    if(!dane.good()) cout << "Blad z otwarciem pliku\n";

    int n;
    double p;
    int liczbaDanych;

    dane >> n >> p;
    dane >> liczbaDanych;

    cout << "n: " << n << ", p: " << p << endl;
    cout << "liczbaDanych: " << liczbaDanych << endl;

    auto* daneTablica = new unsigned int [liczbaDanych];

    for(int i = 0; i < liczbaDanych; i++) {
        dane >> daneTablica [ i ];
    }

  /*  // wyswietlanie danych
    for(int i = 0; i < liczbaDanych; i++) {
        cout << daneTablica[i] << endl;
    }*/

    // ka¿da cecha to inna liczba
    double tabelaChi [n+1] [5];

    //przepisanie wartosci
    for(int i = 0; i < n+1; i++) {
        tabelaChi[i][0] = i;
    }

    // teraz liczymy ich wystapienia
    policzWystapienia(daneTablica, liczbaDanych, tabelaChi,n+1);

    //liczenie wartosci spodziewanej [2]
    for(int i = 0; i < n+1; i++) {
        tabelaChi[i][2] = liczbaDanych*(dwumianNewtona(n, tabelaChi[i][0])*pow(p, tabelaChi[i][0])*pow(1-p, n-tabelaChi[i][0]));
    }


    //liczenie [(obs-exp)^2] [3]
    for(int i = 0; i < n+1; i++) {
        tabelaChi[i][3] = (tabelaChi[i][1]-tabelaChi[i][2])*(tabelaChi[i][1]-tabelaChi[i][2]);
    }

    //liczenie component [4]
    for(int i = 0; i < n+1; i++) {
        tabelaChi[i][4] = tabelaChi[i][3]/tabelaChi[i][2];
    }

    //wyliczenie wartosci empirycznej
    double wartoscEmpiryczna = 0;
    for (int i =0; i < n+1; i++) {
        wartoscEmpiryczna += tabelaChi[i][4];
    }


    cout << "[wartosc] [observed] [expected] [(obs-exp)^2] [(obs-exp)^2/exp]" << endl;

    //wyswietlanie kontrolne liczby wystapien
    for(int i = 0; i < n+1; i++) {
        printf("[%llf] | %llf | %llf | %llf | %llf \n",
               tabelaChi[i][0], tabelaChi[i][1], tabelaChi[i][2], tabelaChi[i][3],
               tabelaChi[i][4]);
    }

    cout << "wartoscEmpiryczna: " << wartoscEmpiryczna << endl;

    delete [] daneTablica;

    return wartoscEmpiryczna;
}

unsigned int znajdzMaksymalnaLiczbe(const unsigned int* dane, int rozmiar) {
    unsigned int max = dane[0];
    for(int i = 1; i < rozmiar; i++) {
        if(max < dane[i]) max = dane[i];
    }
    return max;
}

double chiKwadratGeneratorP() {
    cout.precision(15);

    fstream dane;
    dane.open("generatorP.txt", ios::in);
    if(!dane.good()) cout << "Blad z otwarciem pliku\n";

    double lambda;
    int liczbaDanych;

    dane >> lambda;
    dane >> liczbaDanych;

    cout << "lambda: " << lambda << endl;
    cout << "liczbaDanych: " << liczbaDanych << endl;

    auto* daneTablica = new unsigned int [liczbaDanych];

    for(int i = 0; i < liczbaDanych; i++) {
        dane >> daneTablica [ i ];
    }

   /* // wyswietlanie danych
    for(int i = 0; i < liczbaDanych; i++) {
        cout << daneTablica[i] << endl;
    }*/

    // ka¿da cecha to inna liczba
    // wyznaczamy maksymalna liczbe
    int maxLiczba = znajdzMaksymalnaLiczbe(daneTablica, liczbaDanych);
    int rozmiarTablicyChi = maxLiczba+1;
    double tabelaChi [rozmiarTablicyChi] [5];

    //przepisanie wartosci
    for(int i = 0; i < rozmiarTablicyChi; i++) {
        tabelaChi[i][0] = i;
    }

    // teraz liczymy ich wystapienia
    policzWystapienia(daneTablica, liczbaDanych, tabelaChi,rozmiarTablicyChi);

    //liczenie wartosci spodziewanej [2]
    for(int i = 0; i < rozmiarTablicyChi; i++) {
        tabelaChi[i][2] = liczbaDanych*(exp(-lambda)*pow(lambda, tabelaChi[i][0]))/silnia(tabelaChi[i][0]);
    }


    //liczenie [(obs-exp)^2] [3]
    for(int i = 0; i < rozmiarTablicyChi; i++) {
        tabelaChi[i][3] = (tabelaChi[i][1]-tabelaChi[i][2])*(tabelaChi[i][1]-tabelaChi[i][2]);
    }

    //liczenie component [4]
    for(int i = 0; i < rozmiarTablicyChi; i++) {
        tabelaChi[i][4] = tabelaChi[i][3]/tabelaChi[i][2];
    }

    //wyliczenie wartosci empirycznej
    double wartoscEmpiryczna = 0;
    for (int i =0; i < rozmiarTablicyChi; i++) {
        wartoscEmpiryczna += tabelaChi[i][4];
    }

    cout << "[wartosc] [observed] [expected] [(obs-exp)^2] [(obs-exp)^2/exp]" << endl;

    //wyswietlanie kontrolne liczby wystapien
    for(int i = 0; i < rozmiarTablicyChi; i++) {
        printf("[%llf] | %llf | %llf | %llf | %llf \n",
                tabelaChi[i][0], tabelaChi[i][1], tabelaChi[i][2], tabelaChi[i][3],
               tabelaChi[i][4]);
    }

    cout << "wartoscEmpiryczna: " << wartoscEmpiryczna << endl;

    delete [] daneTablica;

    return wartoscEmpiryczna;
}

void findMinMax(const double* dane, int rozmiarDanych, double& minNumber, double&maxNumber) {
    minNumber = dane[0];
    maxNumber = dane[0];
    for(int i = 1; i < rozmiarDanych; i++) {
        if(minNumber > dane[i]) minNumber = dane[i];
        if(maxNumber < dane[i]) maxNumber = dane[i];
    }
}

double chiKwadratGeneratorW() {
    cout.precision(15);

    fstream dane;
    dane.open("generatorW.txt", ios::in);
    if(!dane.good()) cout << "Blad z otwarciem pliku\n";

    double lambda;
    int liczbaDanych;

    dane >> lambda;
    dane >> liczbaDanych;

    cout << "lambda: " << lambda << endl;
    cout << "liczbaDanych: " << liczbaDanych << endl;

    auto* daneTablica = new double [liczbaDanych];

    for(int i = 0; i < liczbaDanych; i++) {
        dane >> daneTablica [ i ];
    }

  /*  // wyswietlanie danych
    for(int i = 0; i < liczbaDanych; i++) {
        cout << daneTablica[i] << endl;
    }*/

    // bedziemy mieli 10 przedzialow
    int liczbaCech = 20;
    double tabelaChi [liczbaCech] [6];
    // [poczatekPrzedzialu] [koniec przedzialu] [observed] [expected] [(obs-exp)^2] [component (obs-exp)^2/exp]
    //              0               1               2           3           4           5

    //znaleznienie minNumber oraz maxNumber w celu wyznaczenia przedzialow
    double minNumber;
    double maxNumber;
    findMinMax(daneTablica, liczbaDanych, minNumber, maxNumber);
    // inicjalizacja
    cout << "minNumber: " << minNumber << ", maxNumber: " << maxNumber << endl;
    double skokPrzedzialu = (maxNumber-minNumber)/(double)liczbaCech;
    cout << "skok przedzialu: " << skokPrzedzialu << endl;
    tabelaChi[0][0] = minNumber;
    tabelaChi[0][1] = minNumber+skokPrzedzialu;
    for (int i = 1; i < liczbaCech; i++) {
        tabelaChi[i][0] = minNumber+skokPrzedzialu;
        minNumber += skokPrzedzialu;
        tabelaChi[i][1] = minNumber+skokPrzedzialu;
    }

    //liczenie wystapien [observed]
    for(int i = 0; i < liczbaCech; i++) {
        tabelaChi[i][2] = policzWystapieniaWPrzedziale(daneTablica, liczbaDanych, tabelaChi[i][0], tabelaChi[i][1]);
    }

    //liczenie wartosci spodziewanej [3]
    for(int i = 0; i < liczbaCech; i++) {
        tabelaChi[i][3] = liczbaDanych*((1-exp(-lambda*tabelaChi[i][1]))-(1-exp(-lambda*tabelaChi[i][0])));  //tutaj trzeba calke policzyc
    }

    //liczenie [(obs-exp)^2] [4]
    for(int i = 0; i < liczbaCech; i++) {
        tabelaChi[i][4] = (tabelaChi[i][2]-tabelaChi[i][3])*(tabelaChi[i][2]-tabelaChi[i][3]);
    }

    //liczenie component [5]
    for(int i = 0; i < liczbaCech; i++) {
        tabelaChi[i][5] = tabelaChi[i][4]/tabelaChi[i][3];
    }

    //wyliczenie wartosci empirycznej
    double wartoscEmpiryczna = 0;
    for (int i =0; i < liczbaCech; i++) {
        wartoscEmpiryczna += tabelaChi[i][5];
    }

    //wyswietlanie kontrolne liczby wystapien
    cout << "[wartosc]              [observed] [expected] [(obs-exp)^2] [(obs-exp)^2/exp]" << endl;
    for(int i = 0; i < liczbaCech; i++) {
        printf("[%llf, %llf] | %llf | %llf | %llf | %llf \n",
               tabelaChi[i][0], tabelaChi[i][1], tabelaChi[i][2], tabelaChi[i][3],
               tabelaChi[i][4], tabelaChi[i][5]);
    }

/*
    // do wykresu na gestosc prawdopodobienstwa
    for (int i = 0; i < liczbaCech; i++) {
        for(int j = 0; j < 1; j++) {
            printf("%llf| %llf | %llf \n",
                   tabelaChi[i][j], tabelaChi[i][2]/1000, tabelaChi[i][3]/1000);
        }
    }*/


    cout << "wartoscEmpiryczna: " << wartoscEmpiryczna << endl;

    delete [] daneTablica;

    return wartoscEmpiryczna;
}

double dystrybuantaNormalny(double x, double sigma, double mi) {
    return (1/(sigma*sqrt(2*M_PI)))*(-sqrt(M_PI/2)*sigma)*erf((mi - x)/(sqrt(2)*sigma));
}

double chiKwadratGeneratorN() {
    cout.precision(15);

    fstream dane;
    dane.open("generatorN.txt", ios::in);
    if (!dane.good()) cout << "Blad z otwarciem pliku\n";


    double sigma;
    double mi;
    int liczbaDanych;
    dane >> sigma >> mi;
    dane >> liczbaDanych;

    cout << "sigma: " << sigma << ", mi: " << mi << endl;
    cout << "liczbaDanych: " << liczbaDanych << endl;

    auto *daneTablica = new double[liczbaDanych];

    for (int i = 0; i < liczbaDanych; i++) {
        dane >> daneTablica[i];
    }

  /*  // wyswietlanie danych
    for (int i = 0; i < liczbaDanych; i++) {
        cout << daneTablica[i] << endl;
    }*/

    // bedziemy mieli 10 przedzialow
    int liczbaCech = 10;
    double tabelaChi[liczbaCech][6];
    // [poczatekPrzedzialu] [koniec przedzialu] [observed] [expected] [(obs-exp)^2] [component (obs-exp)^2/exp]
    //              0               1               2           3           4           5

    //znaleznienie minNumber oraz maxNumber w celu wyznaczenia przedzialow
    double minNumber;
    double maxNumber;
    findMinMax(daneTablica, liczbaDanych, minNumber, maxNumber);
    // inicjalizacja
    cout << "minNumber: " << minNumber << ", maxNumber: " << maxNumber << endl;
    double skokPrzedzialu = (maxNumber - minNumber) / (double) liczbaCech;
    if(skokPrzedzialu < 0) skokPrzedzialu *= -1;
    cout << "skok przedzialu: " << skokPrzedzialu << endl;
    tabelaChi[0][0] = minNumber;
    tabelaChi[0][1] = minNumber+skokPrzedzialu;
    for (int i = 1; i < liczbaCech; i++) {
        tabelaChi[i][0] = minNumber+skokPrzedzialu;
        minNumber += skokPrzedzialu;
        tabelaChi[i][1] = minNumber+skokPrzedzialu;
    }

    //liczenie wystapien [observed]
    for (int i = 0; i < liczbaCech; i++) {
        tabelaChi[i][2] = policzWystapieniaWPrzedziale(daneTablica, liczbaDanych, tabelaChi[i][0],
                                                             tabelaChi[i][1]);
    }

    //liczenie wartosci spodziewanej [3]
    for (int i = 0; i < liczbaCech; i++) {
        tabelaChi[i][3] = liczbaDanych *(dystrybuantaNormalny(tabelaChi[i][1], sigma, mi)-dystrybuantaNormalny(tabelaChi[i][0], sigma, mi));
    }

    //liczenie [(obs-exp)^2] [4]
    for (int i = 0; i < liczbaCech; i++) {
        tabelaChi[i][4] =
                (tabelaChi[i][2] - tabelaChi[i][3]) * (tabelaChi[i][2] - tabelaChi[i][3]);
    }

    //liczenie component [5]
    for (int i = 0; i < liczbaCech; i++) {
        tabelaChi[i][5] = tabelaChi[i][4] / tabelaChi[i][3];
    }

    //wyliczenie wartosci empirycznej
    double wartoscEmpiryczna = 0;
    for (int i = 0; i < liczbaCech; i++) {
        wartoscEmpiryczna += tabelaChi[i][5];
    }

    //wyswietlanie kontrolne liczby wystapien
    cout << "[wartosc]              [observed] [expected] [(obs-exp)^2] [(obs-exp)^2/exp]" << endl;
    for (int i = 0; i < liczbaCech; i++) {
        printf("[%llf, %llf] | %llf | %llf | %llf | %llf \n",
               tabelaChi[i][0], tabelaChi[i][1], tabelaChi[i][2], tabelaChi[i][3],
               tabelaChi[i][4], tabelaChi[i][5]);
    }
   /*
    * do wykresu na gestosc prawdopodobienstwa
    for (int i = 0; i < liczbaCech; i++) {
        for(int j = 0; j < 1; j++) {
            printf("%llf| %llf | %llf \n",
                   tabelaChi[i][j], tabelaChi[i][2]/1000, tabelaChi[i][3]/1000);
        }
    }
    */

    cout << "wartoscEmpiryczna: " << wartoscEmpiryczna << endl;

    delete [] daneTablica;

    return wartoscEmpiryczna;
}

int main() {
    chiKwadratGeneratorN();
    return 0;
}

