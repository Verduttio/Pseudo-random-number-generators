#include <iostream>
#include <fstream>
#include <algorithm>  //dla sortowania liczb

using namespace std;

void displayArray(const double* array, int size) {
    for(int i = 0; i < size; i++) {
        cout << array[i] << endl;
    }
    cout << endl;
}

double znajdzMediane(const double* array, int arraySize) {
    //sortujemy liczby
    double sortedArray [arraySize];

    //kopiowanie tablicy
    for(int i = 0; i < arraySize; i++) {
        sortedArray[i] = array[i];
    }

    sort(sortedArray, sortedArray+ arraySize);

    if(arraySize%2 != 0) {
        return sortedArray[arraySize/2];
    } else {
        return (sortedArray[arraySize/2]+sortedArray[arraySize/2 - 1])/2.0;
    }
}

void testSerii(const string& nazwaPliku) {
    fstream plik;
    plik.open(nazwaPliku, ios::in);
    if(!plik.good()) cout << "Blad z otwarciem pliku\n";
    // zakładamy strukturę pliku:
    // liczba badanych liczb
    // liczby...
    int liczbaDanych;
    plik >> liczbaDanych;

    double liczby[liczbaDanych];

    //wczytanie liczb
    for(int i = 0; i < liczbaDanych; i++) {
        plik >> liczby[i];
    }

    //znajdujemy mediane
    double mediana = znajdzMediane(liczby, liczbaDanych);

    cout << "mediana: " << mediana << endl;

    //dokonujemy zamiany liczb na A lub B
    // gdy xi < mediana => A
    // gdy xi > mediana => B
    // gdy xi = mediana => pomijamy tę liczbę

    vector<char> ciagi;
    for(int i = 0; i < liczbaDanych; i++) {
        if(liczby[i] < mediana) ciagi.push_back('A');
        else if(liczby[i] > mediana) ciagi.push_back('B');
    }

    for(int i = 0; i < ciagi.size(); i++) {
        cout << ciagi[i] << endl;
    }

    //liczymy serie oraz liczbe wystąpień A i B
    int liczbaSerii = 0;
    int liczbaWystapienA = 0;
    int liczbaWystapienB = 0;

    if(ciagi[0] == 'A') liczbaWystapienA++;
    else liczbaWystapienB++;
    liczbaSerii++;

    for(int i = 1; i < ciagi.size(); i++) {
        if(ciagi[i] == 'A') liczbaWystapienA++;
        else liczbaWystapienB++;

        if(ciagi[i] != ciagi[i-1]) liczbaSerii++;
    }

    cout << "liczba serii: " << liczbaSerii << endl;
    cout << "liczba wystapien A: " << liczbaWystapienA << endl;
    cout << "liczba wystapien B: " << liczbaWystapienB << endl;

    //displayArray(liczby, liczbaDanych);

}


int main() {
    cout.precision(15);
    testSerii("generatorN_testSerii.txt");


    return 0;
}
