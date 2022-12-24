//
// Created by Artur Gubanovich on 18.12.22.
//

#ifndef BAZASTUDENTOWV2_STUDENTMANAGER_H
#define BAZASTUDENTOWV2_STUDENTMANAGER_H

#include "Student.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "TypeOfSortingOfStudents.h"
#include "../../view/ConsoleManager.h"
#include <stdio.h>
#include <vector>
#include <cstring>
#include "../utils/BinaryFileManager.h"

using namespace std;

class StudentManager {

private:

    ConsoleManager consoleManager;

//    link do pliku ze studentami
    string filePath;

    BinaryFileManager<Student> binaryFileManager;

//    Sortowanie studentow według pozycji Średnia ocena
    void sortAverageAsses(TypeOfSortingOfStudents typeOfSort) {
        binaryFileManager.setFilePath(filePath);
        int lastIndex = binaryFileManager.findLastIndexInBinaryFile();
        Student lastStudent;
        Student student;
        bool studentSwaped = false;
        bool isSorted;

        while (true) {
            isSorted = true;
            for (int i = 0; i < lastIndex; i++) {
                student = binaryFileManager.readStudent(i);

                if (i == 0) {
                    lastStudent = student;
                } else if (typeOfSort == ASCENDING) {
                    if (lastStudent.averageOfAssessments > student.averageOfAssessments) {
                        binaryFileManager.swapStudents(i - 1);
                        studentSwaped = true;
                        isSorted = false;
                    }
                    if (!studentSwaped) {
                        lastStudent = student;
                    }
                    studentSwaped = false;
                } else if (typeOfSort == DESCENDING) {
                    if (lastStudent.averageOfAssessments < student.averageOfAssessments) {
                        binaryFileManager.swapStudents(i - 1);
                        studentSwaped = true;
                        isSorted = false;
                    }
                    if (!studentSwaped) {
                        lastStudent = student;
                    }
                    studentSwaped = false;
                }
            }
            if (isSorted) break;
        }
    }

//   Sortowanie studentow według pozycji nazwisko
    void sortSurname(TypeOfSortingOfStudents typeOfSort) {

        binaryFileManager.setFilePath(filePath);
        int lastIndex = binaryFileManager.findLastIndexInBinaryFile();
        Student lastStudent;
        Student student;
        bool studentSwaped = false;
        bool isSorted;

        while (true) {
            isSorted = true;
            for (int i = 0; i < lastIndex; i++) {
                student = binaryFileManager.readStudent(i);

                if (i == 0) {
                    lastStudent = student;
                } else if (typeOfSort == ASCENDING) {
                    vector<string> studentsSurnames = {lastStudent.surname, student.surname};
                    sort(studentsSurnames.begin(), studentsSurnames.end());

                    string firstSortedStudentSurname;
                    for (string temp: studentsSurnames) {
                        firstSortedStudentSurname = temp;
                        break;
                    }

                    if (firstSortedStudentSurname == student.surname) {
                        binaryFileManager.swapStudents(i - 1);
                        studentSwaped = true;
                        isSorted = false;
                    }
                    if (!studentSwaped) {
                        lastStudent = student;
                    }
                    studentSwaped = false;
                } else if (typeOfSort == DESCENDING) {

                    vector<string> studentsSurnames = {lastStudent.surname, student.surname};
                    sort(studentsSurnames.begin(), studentsSurnames.end(), greater<string>());

                    string firstSortedStudentSurname;
                    for (string temp: studentsSurnames) {
                        firstSortedStudentSurname = temp;
                        break;
                    }

                    if (firstSortedStudentSurname == student.surname) {
                        binaryFileManager.swapStudents(i - 1);
                        studentSwaped = true;
                        isSorted = false;
                    }
                    if (!studentSwaped) {
                        lastStudent = student;
                    }
                    studentSwaped = false;
                }
            }
            if (isSorted) break;
        }
    }

public:

    void setFilePath(string filePath) {
        this->filePath = filePath;
    }

//    Wypisywanie danych pliku BazaStudentow do konsoli
    void printData() {
        Student student;
        ifstream reader(filePath, ios::binary);
        for (int i = 0;; i++) {
            reader.read(reinterpret_cast<char *>(&student), sizeof(student));
            if (reader.eof()) break;
            consoleManager.printDataStudent(student, i);
        }
        reader.close();
    }

//    dodawanie studentow do pliku BazaStudentow
    void addStudent() {
        Student student;

        binaryFileManager.setFilePath(filePath);
        int lastIndex = binaryFileManager.findLastIndexInBinaryFile();
        //ignore char po wypisywaniu menu (błąd getline'a)
        consoleManager.ignoreSymbol();

        ofstream writer(filePath, ios::binary | ios::in | ios::ate);
        writer.tellp();
        writer.seekp(sizeof(struct Student) * (lastIndex));
        Student student1;

        student1.name = consoleManager.getNameStudent();

        student1.surname = consoleManager.getSurnameStudent();

        student1.academicYear = consoleManager.getAcademicYear();
        consoleManager.ignoreSymbol();

        student1.courseOfStudy = consoleManager.getCourseOfStudy();

        student1.adres = consoleManager.getAdres();

        student1.averageOfAssessments = consoleManager.getAverageOfAssessments();

        writer.write(reinterpret_cast<char *>(&student1), sizeof(student1));
        writer.close();
    }

//    zmiana danych studentow w pliku BazaStudentow
    void changeDataStudent() {
        int index;
        index = consoleManager.askForIndex(
                "Сhcesz zastąpić wszystkie dane lub konkretny element? 1)wszystkie 2)konkretny element");

        int nr = consoleManager.askForIndex("Podaj nr rekordu do edycji: ");
        consoleManager.ignoreSymbol();

        ofstream writer(filePath, ios::binary | ios::in | ios::ate);
        writer.seekp(sizeof(struct Student) * (nr));
        Student student;
        if (index == 1) {

            student.name = consoleManager.getNameStudent();

            student.surname = consoleManager.getSurnameStudent();

            student.academicYear = consoleManager.getAcademicYear();
            consoleManager.ignoreSymbol();

            student.courseOfStudy = consoleManager.getCourseOfStudy();

            student.adres = consoleManager.getAdres();

            student.averageOfAssessments = consoleManager.getAverageOfAssessments();

            writer.write(reinterpret_cast<char *>(&student), sizeof(student));
            writer.close();
        } else if (index == 2) {

            index = consoleManager.askForIndex(
                    "ktory element chcesz zmienic: 1)imie 2)nazwisko 3)rok studiow 4)kierunek 5)adres 6)srednia z ocen ");

            student = binaryFileManager.readStudent(nr);

            switch (index) {
                case 1:
                    student.name = consoleManager.getNameStudent();
                    break;
                case 2:
                    student.surname = consoleManager.getSurnameStudent();
                    break;
                case 3:
                    student.academicYear = consoleManager.getAcademicYear();
                    break;
                case 4:
                    student.courseOfStudy = consoleManager.getCourseOfStudy();
                    break;
                case 5:
                    student.adres = consoleManager.getAdres();
                    break;
                case 6:
                    student.averageOfAssessments = consoleManager.getAverageOfAssessments();
            }

            writer.write(reinterpret_cast<char *>(&student), sizeof(student));
        }
    }

//    usuwanie danych studenta z pliku
    void removeStudent() {
        int deleteIndex = consoleManager.askForIndex("Podaj numer rekordu");

        ifstream reader(filePath, ios::binary);
        if (!reader)
            consoleManager.printError("Error with file");
        else {
            reader.seekg(0, ios::end);
            int size = reader.tellg();
            size = size / sizeof(Student);
            Student *Students_1 = new Student[size];
            reader.seekg(0, ios::beg);
            reader.read((char *) Students_1, sizeof(Student) * size);
            reader.close();

            ofstream writer(filePath, ios::binary);
            for (int i = 0; i < size; i++) {
                if (i != deleteIndex)
                    writer.write((char *) &Students_1[i], sizeof(Student));
            }
            writer.close();
        }
    }

//    posortowanie dannych studentow w pliku
    void sortStudents(StudentSortingCriteria crit, TypeOfSortingOfStudents typeOfSort) {
        if (crit == AVERAGE_ASSES) {
            sortAverageAsses(typeOfSort);
        } else if (crit == SURNAME) {
            sortSurname(typeOfSort);
        }
    }
};


#endif //BAZASTUDENTOWV2_STUDENTMANAGER_H
