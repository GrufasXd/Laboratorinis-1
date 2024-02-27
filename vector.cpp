#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

struct studentas {
    string vardas;
    string pavarde;
    vector<int> nd;
    int egzas;
};
void skaityti(vector<studentas>& students, vector<double>& galrez, vector<double>& median)
{
    int failas;
    cout << "Is kurio failo skaityti duomenis?" << endl << "10k duomenu - 1" << endl << "100k duomenu - 2" << endl << "1mil duomenu - 3" << endl;
    cin >> failas;
    ifstream inf;
    if (failas == 1)
        inf.open("kursiokai1.txt");
    if (failas == 2)
        inf.open("kursiokai2.txt");
    if (failas == 3)
        inf.open("kursiokai3.txt");
    string firstline;
    getline(inf, firstline);
    studentas tempstud;
    while(inf >> tempstud.vardas >> tempstud.pavarde)
    {
        tempstud.nd.resize(15);
        for(int j = 0; j<15; j++)
        {
            inf >> tempstud.nd[j];
        }
        int n = tempstud.nd.size();
        inf >> tempstud.egzas;
        int ndvid = 0;
        for(int i = 0; i<n; i++)
        {
            ndvid += tempstud.nd[i];
        }
        sort(tempstud.nd.begin(), tempstud.nd.end());
            if (n % 2 == 0) {
                median.push_back((tempstud.nd[n / 2 - 1] + tempstud.nd[n / 2]) / 2.0);
            } else {
                median.push_back(tempstud.nd[n / 2]);
            }

            double vidurkis = (double)ndvid / n;

            galrez.push_back(0.4 * vidurkis + 0.6 * tempstud.egzas);

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
    int kodas;
    int pas;
    int rusis;
    cout << "Ar norite duomenis generuoti / rasyti ranka - 1" << endl << "Ar norite duomenis skaityti is failo - 2" << endl;
    cin >> kodas;
    if(kodas == 1){
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

                cout << "Iveskite egzamino rezultata: ";
                cin >> temp_student.egzas;

            galrez.push_back(0.4 * vidurkis + 0.6 * temp_student.egzas);

            // Add the temporary student to the vectors
            students.push_back(temp_student);
        }
    } while (pas != 4);
    spausdint(students, galrez, median);
    }
    else if(kodas == 2)
    {
    skaityti(students, galrez, median);
    cout << "Kaip norite kad butu surusiuoti duomenis?" << endl << "Pagal varda - 1" << endl << "Pagal pavarde - 2" << endl << "Galutini pazymiu vidurki - 3" << endl << "Galutini pagal mediana - 4" << endl;
    cin >> rusis;
    if(rusis == 1)
    {
    bool keist;
    do
    {
        keist = false;
        for(int i = 0; i < students.size()-1; i++)
        {
            if(students[i].vardas > students[i+1].vardas)
            {
            swap(students[i].vardas, students[i+1].vardas);
            swap(students[i].pavarde, students[i+1].pavarde);
            swap(galrez[i], galrez[i+1]);
            swap(median[i], median[i+1]);
            keist = true;
            }
        }
    }while(keist);
    }
    if(rusis == 2)
    {
    bool keist;
    do
    {
        keist = false;
        for(int i = 0; i < students.size()-1; i++)
        {
            if(students[i].pavarde > students[i+1].pavarde)
            {
            swap(students[i].pavarde, students[i+1].pavarde);
            swap(galrez[i], galrez[i+1]);
            swap(median[i], median[i+1]);
            swap(students[i].vardas, students[i+1].vardas);
            keist = true;
            }
        }
    }while(keist);
    }
    if(rusis == 3)
    {
    bool keist;
    do
    {
        keist = false;
        for(int i = 0; i < students.size()-1; i++)
        {
            if(galrez[i] > galrez[i+1])
            {
            swap(galrez[i], galrez[i+1]);
            swap(median[i], median[i+1]);
            swap(students[i].vardas, students[i+1].vardas);
            swap(students[i].pavarde, students[i+1].pavarde);
            keist = true;
            }
        }
    }while(keist);
    }
    if(rusis == 4)
    {
    bool keist;
    do
    {
        keist = false;
        for(int i = 0; i < students.size()-1; i++)
        {
            if(median[i] > median[i+1])
            {
            swap(median[i], median[i+1]);
            swap(students[i].vardas, students[i+1].vardas);
            swap(students[i].pavarde, students[i+1].pavarde);
            swap(galrez[i], galrez[i+1]);
            keist = true;
            }
        }
    }while(keist);
    }
    int slap;
    cout << "Ar duomenis spausdinti ekrane - 1" << endl << "Ar duomenis spausdint faile - 2" << endl;
    cin >> slap;
    if(slap == 1)
    spausdint(students, galrez, median);
    else if(slap == 2)
    spausdintfaila(students, galrez, median);
    }
    return 0;
}
