#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

#include <string>
#include <vector>
using namespace std;
struct studentas {
    std::string vardas;
    std::string pavarde;
    std::vector<int> nd;
    int egzas;
};
void quickSort(vector<studentas>& students, vector<double>& galrez, vector<double>& median, int low, int high, int rusis);
int partition(vector<studentas>& students, vector<double>& galrez, vector<double>& median, int low, int high, int rusis);
bool isNumeric(const std::string& str);
int readInt(const std::string& prompt);
bool compareNames(const std::string& a, const std::string& b);
void skaityti(std::vector<studentas>& students, std::vector<double>& galrez, std::vector<double>& median);
void spausdint(const std::vector<studentas>& students, const std::vector<double>& galrez, const std::vector<double>& median);
void spausdintfaila(const std::vector<studentas>& students, const std::vector<double>& galrez, const std::vector<double>& median);
void rasytiranka(std::vector<studentas>& students, std::vector<double>& galrez, std::vector<double>& median);
void skaitymas(std::vector<studentas>& students, std::vector<double>& galrez, std::vector<double>& median);
std::string randname();

#endif // FUNKCIJOS_H
