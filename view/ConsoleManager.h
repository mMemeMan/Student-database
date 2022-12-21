//
// Created by Artur Gubanovich on 19.12.22.
//

#ifndef BAZASTUDENTOWV2_CONSOLEMANAGER_H
#define BAZASTUDENTOWV2_CONSOLEMANAGER_H
#include <iostream>

using namespace std;

class ConsoleManager {
private:
    string str;
public:

    string getNameStudent() {
        cout << "Podaj imię: " << endl;
        getline(cin, str);
        return str;
    }

    string getSurnameStudent() {
        cout << "Podaj nazwisko: " << endl;
        getline(cin, str);
        return str;
    }

    short getAcademicYear() {
        cout << "Podaj rok studiow: " << endl;
        int academicYear;
        cin >> academicYear;
        return academicYear;
    }

    string getCourseOfStudy() {
        cout << "Podaj kierunek: " << endl;
        getline(cin, str);
        return str;
    }

    string getAdres() {
        cout << "Podaj adres: " << endl;
        getline(cin, str);
        return str;
    }

    double getAverageOfAssessments(){
        cout << "Podaj sredniu z ocen: " << endl;
        double averageOfAssessments;
        cin >> averageOfAssessments;
        return averageOfAssessments;
    }

    void ignoreSymbol() {
        cin.ignore();
    }

    int printMenu() {
        cout << "1)Pokazać wszystkich studentów"
                " 2)Dodać studenta"
                " 3)Usunąć studenta (niestety)"
                " 4)Posortowanie"
                " 5)Edycja dannych"
                " 6)Skończyć programm" << endl;
        int index;
        cin >> index;
        return index;
    }

    int askForIndex(string str) {
        cout << str << endl;
        int index;
        cin >> index;
        return index;
    }

    int getSortTarget() {
        cout << "Podaj cel sortowania: 1) Średnia z ocen 2) Nazwisko " << endl;
        int target;
        cin >> target;
        return target;
    }

    int getSortCrit() {
        cout << "Podaj kryterium sortowania: 1)Rosnacy 2)Malejacy " << endl;
        int crit;
        cin >> crit;
        return crit;
    }

    void printError(const char *err) {
        perror(err);
        cout << endl;
    }

    void printDataStudent(Student student, int i) {
        cout << "Numer rekordu: " << i << endl;
        cout << student.name << "  " << student.surname << endl;
        cout << "Rok studiow: " << student.academicYear << endl;
        cout << "Kierunek: " << student.courseOfStudy << endl;
        cout << "adres: " << student.adres << endl;
        cout << "Srednia z ocen: " << student.averageOfAssessments << endl;
        cout << "_______________________________" << endl;
    }
};

#endif //BAZASTUDENTOWV2_CONSOLEMANAGER_H
