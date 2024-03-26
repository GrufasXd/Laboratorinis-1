#include <iostream>
#include "funkcijos.h"
#include <algorithm>
#include <ctime>
using namespace std;

int main() {
    srand(time(nullptr));

    vector<studentas> students;
    vector<studentas> vargsai;
    vector<studentas> galva;
    vector<double> galrez;
    vector<double> median;
    int kodas;
    int rusis;
    bool correctInput = false;

    while (!correctInput) {
        try {
            cout << "Ar norite duomenis generuoti / rasyti ranka - 1" << endl << "Ar norite duomenis skaityti is failo - 2" << endl;
            cin >> kodas;

            if (kodas != 1 && kodas != 2) {
                throw "Neteisingas ivesties pasirinkimas.";
            }
            correctInput = true;

            if (kodas == 1) {
                rasytiranka(students, galrez, median);
            } else if (kodas == 2) {
                skaitymas(students, galrez, median);
                int slap;
                bool correctPrintInput = false;

                while (!correctPrintInput) {
                    try {
                        cout << "Ar duomenis spausdinti ekrane - 1" << endl << "Ar duomenis spausdint faile - 2" << endl;
                        cin >> slap;

                        if (slap == 1 || slap == 2) {
                            correctPrintInput = true;
                            if (slap == 1)
                                spausdint(students, galrez, median);
                            else if (slap == 2)
                                spausdintfaila(students, galrez, median);
                        } else {
                            throw "Neteisingas pasirinkimas duomenu spausdinimui.";
                        }
                    } catch (const char* msg) {
                        cerr << msg << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }
            }
        } catch (const char* msg) {
            cerr << "Klaida: " << msg << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    return 0;
}
