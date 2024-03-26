    #include "funkcijos.h"
    #include <iostream>
    #include <fstream>
    #include <algorithm>
    #include <numeric>
    #include <cstdlib>
    #include <ctime>
    #include <iomanip>

    using namespace std;

void createfile(const string& filename, const int& kiekis) {
    ofstream inf(filename);

    const int ilgis = 20;
    inf << setw(ilgis) << left << "Vardas" << " " << setw(ilgis) << left << "Pavarde" << "     ";
    for (int i = 1; i < 16; i++) {
        inf << setw(10) << left << "ND" + to_string(i);
    }
    inf << setw(10) << left << "Egz." << endl;

    for (int j = 1; j < kiekis+1; j++) {
        inf << setw(ilgis) << left << "Vardas" + to_string(j) << " " << setw(ilgis) << left << "Pavarde" + to_string(j) << "     ";
        for (int i = 0; i < 15; i++) {
            inf << setw(10) << left << rand() % 10 + 1;
        }
        inf << setw(10) << left << rand() % 10 + 1 << endl;
    }

    inf.close();
}


bool isNumeric(const string& str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

int readInt(const string& prompt) {
    string input;
    cout << prompt;
    cin >> input;

    if (!isNumeric(input)) {
        throw invalid_argument("Klaida: Įvestas tekstas, prašome įvesti skaičių.");
    }

    return stoi(input);
}
    bool compareNames(const string& a, const string& b) {
        string numA, numB;
        for (char c : a) {
            if (isdigit(c)) {
                numA += c;
            }
        }

        for (char c : b) {
            if (isdigit(c)) {
                numB += c;
            }
        }

        int intA = stoi(numA);
        int intB = stoi(numB);

        return intA > intB;
    }
    void skaityti(vector<studentas>& students, vector<double>& galrez, vector<double>& median) {
    int failas;
    cout << "Is kurio failo skaityti duomenis?" << endl << "10k duomenu - 1" << endl << "100k duomenu - 2" << endl << "1mil duomenu - 3" << endl;
    cin >> failas;
    ifstream inf;
    if (failas == 1)
        inf.open("kursiokai1.txt");
    else if (failas == 2)
        inf.open("kursiokai2.txt");
    else if (failas == 3)
        inf.open("kursiokai3.txt");
    else {
        throw "Neteisingas failo pasirinkimas.";
    }

    if (!inf.is_open()) {
        throw "Failo atidaryti nepavyko!";
    }

    string firstline;
    getline(inf, firstline);

    studentas tempstud;
    while (inf >> tempstud.vardas >> tempstud.pavarde) {
        tempstud.nd.clear(); 
        int num_grades;
        if (failas == 1)
            num_grades = 15;
        else if (failas == 2)
            num_grades = 20;
        else if (failas == 3)
            num_grades = 7;

        tempstud.nd.resize(num_grades);
        for (int j = 0; j < num_grades; j++) {
            inf >> tempstud.nd[j];
        }

        inf >> tempstud.egzas;

        sort(tempstud.nd.begin(), tempstud.nd.end());
        double median_value;
        int n = tempstud.nd.size();
        if (n % 2 == 0) {
            median_value = (tempstud.nd[n / 2 - 1] + tempstud.nd[n / 2]) / 2.0;
        } else {
            median_value = tempstud.nd[n / 2];
        }
        double nd_sum = accumulate(tempstud.nd.begin(), tempstud.nd.end(), 0);
        double vidurkis = nd_sum / n;
        double galutinis = 0.4 * vidurkis + 0.6 * tempstud.egzas;

        median.push_back(median_value);
        galrez.push_back(galutinis);
        students.push_back(tempstud);
    }

    inf.close();
}


    void spausdint(const vector<studentas>& students, const vector<double>& galrez, const vector<double>& median) {
        const int ilgis = 20;
        cout << setw(ilgis) << left << "Pavarde" << " " << setw(ilgis) << left << "Vardas" << "     " << setw(ilgis) << left << "Galutinis (Vid. ) / Galutinis (Med. )" << endl;
        cout << "..................................................................." << endl;
        cout << fixed << setprecision(2);

        for (size_t j = 0; j < students.size(); j++) {
            cout << setw(ilgis) << left << students[j].pavarde << " " << setw(ilgis) << left << students[j].vardas << "       " << setw(ilgis) << left << galrez[j] << "      " << setw(ilgis) << left << median[j] << endl;
        }
    }
    void spausdintfaila(const vector<studentas>& students, const vector<double>& galrez, const vector<double>& median) {
        ofstream outf("outputas.txt");

        const int ilgis = 20;
        outf << setw(ilgis) << left << "Pavarde" << " " << setw(ilgis) << left << "Vardas" << "     " << setw(ilgis) << left << "Galutinis (Vid. ) / Galutinis (Med. )" << endl;
        outf << "..................................................................." << endl;
        outf << fixed << setprecision(2);

        for (size_t j = 0; j < students.size(); j++) {
            outf << setw(ilgis) << left << students[j].pavarde << " " << setw(ilgis) << left << students[j].vardas << "       " << setw(ilgis) << left << galrez[j] << "      " << setw(ilgis) << left << median[j] << endl;
        }

        outf.close();
    }

void rasytiranka(vector<studentas>& students, vector<double>& galrez, vector<double>& median) {
    int pas;
    bool reiksme1 = false;
    
    do {
        try {
            cout << "Viska rasyti ranka - 1" << endl << "Generuoti tik pazymius - 2" << endl << "Generuoti ir pazymius ir studentu vardus, pavardes - 3" << endl << "Baigti darba - 4" << endl;
            cin >> pas;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw "Netinkamas ivesties pasirinkimas";
            }
            if (pas == 1 || pas == 2 || pas == 3 || pas == 4) {
                studentas temp_student;
                reiksme1 = true;
                if (pas == 3) {
                    temp_student.vardas = randname();
                    temp_student.pavarde = randname();
                } else if (pas == 1 || pas == 2) {
                    cout << "Iveskite studento varda: ";
                    cin >> temp_student.vardas;

                    cout << "Iveskite studento pavarde: ";
                    cin >> temp_student.pavarde;
                }

                if (pas != 4) {
                    bool reiksme2 = false;
                    while (!reiksme2) {
                        try {
                            int n;
                            cout << "Iveskite studento pazymiu kieki: ";
                            cin >> n;
                            if (cin.fail() || n <= 0) {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                throw "Netinkamas ivesties pasirinkimas";
                            }
                            reiksme2 = true;
                            temp_student.nd.resize(n);

                            int ndvid = 0;
                            for (int i = 0; i < n; i++) {
                                bool reiksme3 = false;
                                while (!reiksme3) {
                                    try {
                                        if (pas == 2 || pas == 3)
                                            temp_student.nd[i] = rand() % 10 + 1;
                                        else {
                                            cout << "Iveskite pazymi: ";
                                            cin >> temp_student.nd[i];
                                            if (cin.fail() || temp_student.nd[i] < 0 || temp_student.nd[i] > 10) {
                                                cin.clear();
                                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                                throw "Netinkamas ivesties pasirinkimas";
                                            }
                                        }
                                        reiksme3 = true;
                                    } catch (const char* msg) {
                                        cerr << msg << endl;
                                    }
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

                            bool reiksme4 = false;
                            while (!reiksme4) {
                                try {
                                    cout << "Iveskite egzamino rezultata: ";
                                    cin >> temp_student.egzas;
                                    if (cin.fail() || temp_student.egzas < 0 || temp_student.egzas > 10) {
                                        cin.clear();
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                        throw "Netinkamas ivesties pasirinkimas";
                                    }
                                    reiksme4 = true;
                                } catch (const char* msg) {
                                    cerr << msg << endl;
                                }
                            }

                            galrez.push_back(0.4 * vidurkis + 0.6 * temp_student.egzas);
                            students.push_back(temp_student);
                        } catch (const char* msg) {
                            cerr << msg << endl;
                        }
                    }
                }
            } else {
                throw "Neteisingas duomenu ivedimo pasirinkimas";
            }
        } catch (const char* msg) {
            cerr << msg << endl;
            reiksme1 = false;
        }
    } while (pas != 4);
    spausdint(students, galrez, median);
}

    void skaitymas(vector<studentas>& students, vector<double>& galrez, vector<double>& median)
    {
        int rusis;
        try {
              skaityti(students, galrez, median);
            } catch (const char* msg) {
                cerr << msg << endl;
                exit(1);
            }
            try {
                cout << "Kaip norite kad butu surusiuoti duomenis?" << endl << "Pagal varda - 1" << endl << "Pagal pavarde - 2" << endl << "Galutini pazymiu vidurki - 3" << endl << "Galutini pagal mediana - 4" << endl;
                cin >> rusis;
                bool keist;
                if (rusis == 1) {
                    do {
                        keist = false;
                        for (int i = 0; i < students.size() - 1; i++) {
                            if (compareNames(students[i].vardas, students[i + 1].vardas)) {
                                swap(students[i].vardas, students[i + 1].vardas);
                                swap(students[i].pavarde, students[i + 1].pavarde);
                                swap(galrez[i], galrez[i + 1]);
                                swap(median[i], median[i + 1]);
                                keist = true;
                            }
                        }
                    } while (keist);
                }
                else if (rusis == 2) {
                    do {
                        keist = false;
                        for (int i = 0; i < students.size() - 1; i++) {
                            if (compareNames(students[i].pavarde, students[i + 1].pavarde)) {
                                swap(students[i].pavarde, students[i + 1].pavarde);
                                swap(galrez[i], galrez[i + 1]);
                                swap(median[i], median[i + 1]);
                                swap(students[i].vardas, students[i + 1].vardas);
                                keist = true;
                            }
                        }
                    } while (keist);
                }
                else if (rusis == 3) {
                    do {
                        keist = false;
                        for (int i = 0; i < students.size() - 1; i++) {
                            if (galrez[i] > galrez[i + 1]) {
                                swap(galrez[i], galrez[i + 1]);
                                swap(median[i], median[i + 1]);
                                swap(students[i].vardas, students[i + 1].vardas);
                                swap(students[i].pavarde, students[i + 1].pavarde);
                                keist = true;
                            }
                        }
                    } while (keist);
                }
                else if (rusis == 4) {
                    do {
                        keist = false;
                        for (int i = 0; i < students.size() - 1; i++) {
                            if (median[i] > median[i + 1]) {
                                swap(median[i], median[i + 1]);
                                swap(students[i].vardas, students[i + 1].vardas);
                                swap(students[i].pavarde, students[i + 1].pavarde);
                                swap(galrez[i], galrez[i + 1]);
                                keist = true;
                            }
                        }
                    } while (keist);
                } else {
                    throw "Neteisingas rusiavimo pasirinkimas";
                }
            } catch (const char* msg) {
                cerr << msg << endl;
                exit(1);
            }
    }

    string randname() {
        string randomString;
        int length = rand() % 20 + 1;
        for (int i = 0; i < length; ++i) {
            randomString += 'a' + rand() % 26; // Random lowercase letter between 'a' and 'z'
        }
        return randomString;
    }
