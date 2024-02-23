#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

struct studentas {
    string vardas;
    string pavarde;
    vector<int> nd;
    int egzas;
};

void spausdint(const vector<studentas>& students, const vector<double>& galrez, const vector<double>& median) {
    const int ilgis = 20;
    cout << setw(ilgis) << left << "Pavarde" << " " << setw(ilgis) << left << "Vardas" << "     " << setw(ilgis) << left << "Galutinis (Vid. ) / Galutinis (Med. )" << endl;
    cout << "..................................................................." << endl;
    cout << fixed << setprecision(2);

    for (size_t j = 0; j < students.size(); j++) {
        cout << setw(ilgis) << left << students[j].pavarde << " " << setw(ilgis) << left << students[j].vardas << "       " << setw(ilgis) << left << galrez[j] << "      " << setw(ilgis) << left << median[j] << endl;
    }
}

string randname() {
    string randomString;
    int length = rand() % 20 + 1; // Random length between 1 and 20 characters
    for (int i = 0; i < length; ++i) {
        randomString += 'a' + rand() % 26; // Random lowercase letter between 'a' and 'z'
    }
    return randomString;
}

int main() {
    srand(time(nullptr));

    vector<studentas> students;
    vector<double> galrez;
    vector<double> median;

    int pas;
    do {
        cout << "Viska rasyti ranka - 1" << endl << "Generuoti tik pazymius - 2" << endl << "Generuoti ir pazymius ir studentu vardus, pavardes - 3" << endl << "Baigti darba - 4" << endl;
        cin >> pas;

        if (pas == 1 || pas == 2 || pas == 3) {
            studentas temp_student;

            if (pas == 3) {
                temp_student.vardas = randname();
                temp_student.pavarde = randname();
            } else {
                cout << "Iveskite studento varda: ";
                cin >> temp_student.vardas;

                cout << "Iveskite studento pavarde: ";
                cin >> temp_student.pavarde;
            }

            int n;
            cout << "Iveskite studento pazymiu kieki: ";
            cin >> n;

            temp_student.nd.resize(n);

            int ndvid = 0;
            for (int i = 0; i < n; i++) {
                if (pas == 2 || pas == 3)
                    temp_student.nd[i] = rand() % 10 + 1;
                else {
                    cout << "Iveskite pazymi: ";
                    cin >> temp_student.nd[i];
                }
                ndvid += temp_student.nd[i];
            }
            sort(temp_student.nd.begin(), temp_student.nd.end());
            if (n % 2 == 0) {
                median.push_back((temp_student.nd[n / 2 - 1] + temp_student.nd[n / 2]) / 2.0);
            } else {
                median.push_back(temp_student.nd[n / 2]);
            }

            double vidurkis = (double)ndvid / n;

            if (pas == 2 || pas == 3)
                temp_student.egzas = rand() % 10 + 1;
            else {
                cout << "Iveskite egzamino rezultata: ";
                cin >> temp_student.egzas;
            }

            galrez.push_back(0.4 * vidurkis + 0.6 * temp_student.egzas);

            // Add the temporary student to the vectors
            students.push_back(temp_student);
        }
    } while (pas != 4);

    spausdint(students, galrez, median);

    return 0;
}
