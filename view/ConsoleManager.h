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
        string academicYear;
        do {
            cout << "Podaj rok studiow: " << endl;
            cin >> academicYear;
        } while (!checkCorrectnessEnteredNumber(academicYear));
        return stoi(academicYear);
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

    double getAverageOfAssessments() {
        string averageOfAssessments;
        do {
            cout << "Podaj sredniu z ocen: " << endl;
            cin >> averageOfAssessments;
        } while (!checkCorrectnessEnteredNumber(averageOfAssessments));
        return stod(averageOfAssessments);
    }

    void ignoreSymbol() {
        cin.ignore();
    }

    int printMenu() {
        str = "1)Pokazać wszystkich studentów"
              " 2)Dodać studenta"
              " 3)Usunąć studenta (niestety)"
              " 4)Posortowanie"
              " 5)Edycja dannych"
              " 6)Skończyć programm";
        int index = askForIndex(str);
        return index;
    }

    int askForIndex(string str) {
        string index;
        do {
            cout << str << endl;
            cin >> index;
        } while (!checkCorrectnessEnteredNumber(index));
        return stoi(index);
    }

    void printError(string err) {
        cout << endl << "---ERROR: " << err << endl << endl;
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

//    sprawdzanie poprawności wprowadzonej liczby
    bool checkCorrectnessEnteredNumber(const string &num) {
        for (char x: num)
            if (!(isdigit(x) || x == '.' || x == ','))
                return false;
        return true;
    }

};

#endif //BAZASTUDENTOWV2_CONSOLEMANAGER_H
