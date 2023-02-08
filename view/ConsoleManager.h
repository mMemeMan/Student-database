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

    void getNameStudent(Student *student) {
        do {
            str = "";

//        czyszczenie tablicy
            memset(student->name, 0, sizeof(int) * NAME_SIZE);

            string temp = "";
            cout << "Podaj imie: " << endl;
            getline(cin, str);

        } while(str.length() > NAME_SIZE);

        str.copy(student->name, NAME_SIZE);
    }

    void getSurnameStudent(Student *student) {
        do {
            str = "";

//        czyszczenie tablicy
            memset(student->surname, 0, sizeof(int) * SURNAME_SIZE);

            string temp = "";
            cout << "Podaj nazwisko: " << endl;
            getline(cin, str);

        } while(str.length() > SURNAME_SIZE);

        str.copy(student->surname, SURNAME_SIZE);
    }

    short getAcademicYear() {
        string academicYear;
        do {
            cout << "Podaj rok studiow [1;4]: " << endl;
            cin >> academicYear;
        } while (!checkCorrectnessEnteredNumber(academicYear)
                 || (stod(academicYear) < 1)
                 || (stod(academicYear) > 4));
        return stoi(academicYear);
    }

    void getCourseOfStudy(Student *student) {
        do {
            str = "";

//        czyszczenie tablicy
            memset(student->courseOfStudy, 0, sizeof(int) * СOURSE_STUDY_SIZE);

            string temp = "";
            cout << "Podaj kierunek: " << endl;
            getline(cin, str);

        } while(str.length() > СOURSE_STUDY_SIZE);

        str.copy(student->courseOfStudy, СOURSE_STUDY_SIZE);
    }

    void getAdres(Student *student) {
        do {
            str = "";

//        czyszczenie tablicy
            memset(student->adres, 0, sizeof(int) * ADRES_SIZE);

            string temp = "";
            cout << "Podaj adres: " << endl;
            getline(cin, str);

        } while(str.length()+1 > ADRES_SIZE);

        str.copy(student->adres, ADRES_SIZE);
    }

    double getAverageOfAssessments() {
        string averageOfAssessments;
        do {
            cout << "Podaj sredniu z ocen [0; 6]: " << endl;
            cin >> averageOfAssessments;
        } while ((!checkCorrectnessEnteredNumber(averageOfAssessments))
                 || (stod(averageOfAssessments) < 0)
                 || (stod(averageOfAssessments) > 6));

        return stod(averageOfAssessments);
    }

    void ignoreSymbol() {
        cin.ignore();
    }

    int printMenu() {
        str = "1)Pokazać wszystkich studentów\n"
              "2)Dodać studenta\n"
              "3)Usunąć studenta (niestety)\n"
              "4)Posortowanie\n"
              "5)Edycja dannych\n"
              "6)Skończyć programm";
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
