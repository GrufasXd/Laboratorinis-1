#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct studentas {
    string vardas;
    string pavarde;
    vector<int> nd;
    int egzas;
};

void spausdint(vector<studentas>& students, vector<double>& galrez, vector<double>& median) {
    cout << "Pavarde" << "  " << "Vardas" << "  " << "Galutinis (Vid. ) / Galutinis (Med. )" << endl;
    cout << "..................................................................." << endl;
    cout << fixed << setprecision(2);

    for (size_t j = 0; j < students.size(); j++) {
        cout << students[j].pavarde << "          " << students[j].vardas << "                " << galrez[j] << "                " << median[j] << endl;
    }
}

int main() {
    int studsk;
    cout << "Iveskite studentu skaiciu: ";
    cin >> studsk;

    vector<studentas> students(studsk);
    vector<double> galrez(studsk);
    vector<double> median(studsk);

    for (int j = 0; j < studsk; j++) {
        cout << "Iveskite studento varda: ";
        cin >> students[j].vardas;

        cout << "Iveskite studento pavarde: ";
        cin >> students[j].pavarde;

        int n;
        cout << "Iveskite studento pazymiu kieki: ";
        cin >> n;

        students[j].nd.resize(n);

        int ndvid = 0;
        for (int i = 0; i < n; i++) {
            cout << "Iveskite pazymi: ";
            cin >> students[j].nd[i];
            ndvid += students[j].nd[i];
        }
        sort(students[j].nd.begin(), students[j].nd.end());
        if (n % 2 == 0) {
            median[j] = (students[j].nd[n / 2 - 1] + students[j].nd[n / 2]) / 2.0;
        } else {
            median[j] = students[j].nd[n / 2];
        }

        double vidurkis = (double)ndvid / n;

        cout << "Iveskite egzamino rezultata: ";
        cin >> students[j].egzas;

        galrez[j] = 0.4 * vidurkis + 0.6 * students[j].egzas;
    }

    spausdint(students, galrez, median);

    return 0;
}
