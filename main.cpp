#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

struct studentas {
    string vardas;
    string pavarde;
    int *nd;
    int egzas;
};

void spausdint(studentas students[], int& studsk, double galrez[], double median[]) {
    const int ilgis = 20;
    cout << setw(ilgis) << left << "Pavarde" << " " << setw(ilgis) << left << "Vardas" << "     " << setw(ilgis) << left <<"Galutinis (Vid. ) / Galutinis (Med. )" << endl;
    cout << "..................................................................." << endl;
    cout << fixed << setprecision(2);

    for (int j = 0; j < studsk; j++) {
        cout << setw(ilgis) << left << students[j].pavarde << " " << setw(ilgis) << left << students[j].vardas << "       " << setw(ilgis) << left << galrez[j] << "      " << setw(ilgis) << left << median[j] << endl;
    }
}

int main() {
    int studsk;
    cout << "Iveskite studentu skaiciu: ";
    cin >> studsk;
    studentas *students = new studentas[studsk];
    double *galrez = new double[studsk];
    double *median = new double[studsk];

    // Seed the random number generator
    srand(time(nullptr));

    for (int j = 0; j < studsk; j++) {
        cout << "Iveskite studento varda: ";
        cin >> students[j].vardas;

        cout << "Iveskite studento pavarde: ";
        cin >> students[j].pavarde;

        int n;
        cout << "Iveskite studento pazymiu kieki: ";
        cin >> n;

        students[j].nd = new int[n];

        int ndvid = 0;
        for (int i = 0; i < n; i++) {
            students[j].nd[i] = rand() % 10 + 1;
            ndvid += students[j].nd[i];
        }
        sort(students[j].nd, students[j].nd + n);
        if (n % 2 == 0) {
            median[j] = (students[j].nd[n / 2 - 1] + students[j].nd[n / 2]) / 2.0;
        } else {
            median[j] = students[j].nd[n / 2];
        }

        double vidurkis = (double)ndvid / n;

        students[j].egzas = rand() % 10 + 1;

        galrez[j] = 0.4 * vidurkis + 0.6 * students[j].egzas;
    }

    spausdint(students, studsk, galrez, median);

    for (int j = 0; j < studsk; j++) {
        delete[] students[j].nd;
    }
    delete[] students;
    delete[] galrez;
    delete[] median;
    return 0;
}
