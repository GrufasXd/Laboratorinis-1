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
    cout << setw(ilgis) << left << "Pavarde" << " " << setw(ilgis) << left << "Vardas" << "     " << setw(ilgis) << left << "Galutinis (Vid. ) / Galutinis (Med. )" << endl;
    cout << "..................................................................." << endl;
    cout << fixed << setprecision(2);

    for (int j = 0; j < studsk; j++) {
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

    int studsk = 0; // Initialize student count to zero
    studentas *students = nullptr;
    double *galrez = nullptr;
    double *median = nullptr;

    int pas;
    do {
        cout << "Viska rasyti ranka - 1" << endl << "Generuoti tik pazymius - 2" << endl << "Generuoti ir pazymius ir studentu vardus, pavardes - 3" << endl << "Baigti darba - 4" << endl;
        cin >> pas;

        if (pas == 1 || pas == 2 || pas == 3) {
            // Increase the size of arrays to accommodate new student
            studentas *temp_students = new studentas[studsk + 1];
            double *temp_galrez = new double[studsk + 1];
            double *temp_median = new double[studsk + 1];

            // Copy existing data to temporary arrays
            for (int j = 0; j < studsk; ++j) {
                temp_students[j] = students[j];
                temp_galrez[j] = galrez[j];
                temp_median[j] = median[j];
            }

            // Delete old arrays
            delete[] students;
            delete[] galrez;
            delete[] median;

            // Point old arrays to new ones
            students = temp_students;
            galrez = temp_galrez;
            median = temp_median;

            if (pas == 3) {
                // Generate random name and last name
                students[studsk].vardas = randname();
                students[studsk].pavarde = randname();
            } else {
                cout << "Iveskite studento varda: ";
                cin >> students[studsk].vardas;

                cout << "Iveskite studento pavarde: ";
                cin >> students[studsk].pavarde;
            }

            int n;
            cout << "Iveskite studento pazymiu kieki: ";
            cin >> n;

            students[studsk].nd = new int[n];

            int ndvid = 0;
            for (int i = 0; i < n; i++) {
                if (pas == 2 || pas == 3)
                    students[studsk].nd[i] = rand() % 10 + 1;
                else {
                    cout << "Iveskite pazymi: ";
                    cin >> students[studsk].nd[i];
                }
                ndvid += students[studsk].nd[i];
            }
            sort(students[studsk].nd, students[studsk].nd + n);
            if (n % 2 == 0) {
                median[studsk] = (students[studsk].nd[n / 2 - 1] + students[studsk].nd[n / 2]) / 2.0;
            } else {
                median[studsk] = students[studsk].nd[n / 2];
            }

            double vidurkis = (double)ndvid / n;

                cout << "Iveskite egzamino rezultata: ";
                cin >> students[studsk].egzas;

            galrez[studsk] = 0.4 * vidurkis + 0.6 * students[studsk].egzas;

            // Increment student count
            studsk++;
        }
    } while (pas != 4);

    spausdint(students, studsk, galrez, median);

    // Free memory
    for (int j = 0; j < studsk; j++) {
        delete[] students[j].nd;
    }
    delete[] students;
    delete[] galrez;
    delete[] median;

    return 0;
}
