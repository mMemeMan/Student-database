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
                student = binaryFileManager.readElement(i);

                if (i == 0) {
                    lastStudent = student;
                } else if (typeOfSort == ASCENDING) {
                    if (lastStudent.averageOfAssessments > student.averageOfAssessments) {
                        binaryFileManager.swapElements(i - 1);
                        studentSwaped = true;
                        isSorted = false;
                    }
                    if (!studentSwaped) {
                        lastStudent = student;
                    }
                    studentSwaped = false;
                } else if (typeOfSort == DESCENDING) {
                    if (lastStudent.averageOfAssessments < student.averageOfAssessments) {
                        binaryFileManager.swapElements(i - 1);
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
                student = binaryFileManager.readElement(i);

                if (i == 0) {
                    lastStudent = student;
                } else if (typeOfSort == ASCENDING) {
                    if (lastStudent.surname != student.surname) {
                        string lastTemp = lastStudent.surname;
                        string temp = student.surname;
                        if (lastTemp.compare(temp) < 0) {
                            binaryFileManager.swapElements(i - 1);
                            studentSwaped = true;
                            isSorted = false;
                        }
                        if (!studentSwaped) {
                            lastStudent = student;
                        }
                        studentSwaped = false;
                    }
                } else if (typeOfSort == DESCENDING) {
                    if (lastStudent.surname != student.surname) {

                        string lastTemp = lastStudent.surname;
                        string temp = student.surname;
                        if (lastTemp.compare(temp) > 0) {
                            binaryFileManager.swapElements(i - 1);
                            studentSwaped = true;
                            isSorted = false;
                        }
                        if (!studentSwaped) {
                            lastStudent = student;
                        }
                        studentSwaped = false;
                    }
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
        if (!reader) {
            consoleManager.printError("Error with file");
        } else {
            for (int i = 0;; i++) {
                reader.read(reinterpret_cast<char *>(&student), sizeof(student));
                if (reader.eof()) break;
                consoleManager.printDataStudent(student, i);
            }
            reader.close();
        }
    }

//    dodawanie studentow do pliku BazaStudentow
    void addStudent() {
        Student student;

        binaryFileManager.setFilePath(filePath);
        int lastIndex = binaryFileManager.findLastIndexInBinaryFile();
        //ignore char po wypisywaniu menu (błąd getline'a)
        consoleManager.ignoreSymbol();

        ofstream writer(filePath, ios::binary | ios::in | ios::ate);

        if (!writer) {
            consoleManager.printError("Error with file");
        } else {
            writer.tellp();
            writer.seekp(sizeof(struct Student) * (lastIndex));
            Student student1;

            consoleManager.getNameStudent(&student1);

            consoleManager.getSurnameStudent(&student1);


            student1.academicYear = consoleManager.getAcademicYear();
            consoleManager.ignoreSymbol();

            consoleManager.getCourseOfStudy(&student1);

            consoleManager.getAdres(&student1);

            student1.averageOfAssessments = consoleManager.getAverageOfAssessments();

            writer.write(reinterpret_cast<char *>(&student1), sizeof(student1));
            writer.close();
        }
    }

//    zmiana danych studentow w pliku BazaStudentow
    void changeDataStudent() {
        binaryFileManager.setFilePath(filePath);

        int index;
        index = consoleManager.askForIndex(
                "Сhcesz zastąpić wszystkie dane lub konkretny element? 1)wszystkie 2)konkretny element");

        int nr = consoleManager.askForIndex("Podaj nr rekordu do edycji: ");
        consoleManager.ignoreSymbol();

        ofstream writer(filePath, ios::binary | ios::in | ios::ate);

        if (!writer) {
            consoleManager.printError("Error with file");
        } else {
            writer.seekp(sizeof(struct Student) * (nr));
            Student student;
            if (index == 1) {

                consoleManager.getNameStudent(&student);

                consoleManager.getSurnameStudent(&student);

                student.academicYear = consoleManager.getAcademicYear();
                consoleManager.ignoreSymbol();

                consoleManager.getCourseOfStudy(&student);

                consoleManager.getAdres(&student);

                student.averageOfAssessments = consoleManager.getAverageOfAssessments();

                writer.write(reinterpret_cast<char *>(&student), sizeof(student));
                writer.close();
            } else if (index == 2) {

                index = consoleManager.askForIndex(
                        "ktory element chcesz zmienic: 1)imie 2)nazwisko 3)rok studiow 4)kierunek 5)adres 6)srednia z ocen ");

                student = binaryFileManager.readElement(nr);
                Student tempStudent;

                switch (index) {
                    case 1:
                        consoleManager.ignoreSymbol();
                        consoleManager.getNameStudent(&tempStudent);
                        tempStudent.surname = student.surname;
                        tempStudent.academicYear = student.academicYear;
                        tempStudent.courseOfStudy = student.courseOfStudy;
                        tempStudent.adres = student.adres;
                        tempStudent.averageOfAssessments = student.averageOfAssessments;
                        break;
                    case 2:
                        consoleManager.ignoreSymbol();
                        consoleManager.getSurnameStudent(&tempStudent);
                        tempStudent.name = student.name;
                        tempStudent.academicYear = student.academicYear;
                        tempStudent.courseOfStudy = student.courseOfStudy;
                        tempStudent.adres = student.adres;
                        tempStudent.averageOfAssessments = student.averageOfAssessments;
                        break;
                    case 3:
                        tempStudent.academicYear = consoleManager.getAcademicYear();
                        tempStudent.name = student.name;
                        tempStudent.surname = student.surname;
                        tempStudent.courseOfStudy = student.courseOfStudy;
                        tempStudent.adres = student.adres;
                        tempStudent.averageOfAssessments = student.averageOfAssessments;
                        break;
                    case 4:
                        consoleManager.ignoreSymbol();
                        consoleManager.getCourseOfStudy(&tempStudent);
                        tempStudent.name = student.name;
                        tempStudent.surname = student.surname;
                        tempStudent.academicYear = student.academicYear;
                        tempStudent.adres = student.adres;
                        tempStudent.averageOfAssessments = student.averageOfAssessments;
                        break;
                    case 5:
                        consoleManager.ignoreSymbol();
                        consoleManager.getAdres(&tempStudent);
                        tempStudent.name = student.name;
                        tempStudent.surname = student.surname;
                        tempStudent.academicYear = student.academicYear;
                        tempStudent.courseOfStudy = student.courseOfStudy;
                        tempStudent.averageOfAssessments = student.averageOfAssessments;
                        break;
                    case 6:
                        student.averageOfAssessments = consoleManager.getAverageOfAssessments();
                        tempStudent.name = student.name;
                        tempStudent.surname = student.surname;
                        tempStudent.academicYear = student.academicYear;
                        tempStudent.courseOfStudy = student.courseOfStudy;
                        tempStudent.adres = student.adres;
                }

                writer.write(reinterpret_cast<char *>(&tempStudent), sizeof(tempStudent));
            } else {
                consoleManager.printError("Nieprawidłowy indeks");
            }
        }
    }

//    usuwanie danych studenta z pliku
    void removeStudent() {
        int deleteIndex = consoleManager.askForIndex("Podaj numer rekordu");

        char tempFileName[] = "tempFile.dat";

        ifstream reader(filePath, ios::binary);

        ofstream writer(tempFileName, ios::binary);

        if (!reader) {
            consoleManager.printError("Error with file");
        } else {
            binaryFileManager.setFilePath(filePath);
            int lastIndex = binaryFileManager.findLastIndexInBinaryFile();

            Student student;

            for (int i = 0; i < lastIndex; i++) {
                if (reader.eof()) break;
                reader.read(reinterpret_cast<char *>(&student), sizeof(student));
                if (i != deleteIndex) {
                    writer.write(reinterpret_cast<char *>(&student), sizeof(student));
                }
            }
            writer.close();
            reader.close();

            binaryFileManager.fileSubstitute(filePath, tempFileName);
        }
    }

//    posortowanie dannych studentow w pliku
    void sortStudents(StudentSortingCriteria crit, TypeOfSortingOfStudents typeOfSort) {
        if (crit == AVERAGE_ASSES) {
            sortAverageAsses(typeOfSort);
        } else if (crit == SURNAME) {
            sortSurname(typeOfSort);
        } else {
            consoleManager.printError("Nieprawidłowy indeks");
        }
    }
};


#endif //BAZASTUDENTOWV2_STUDENTMANAGER_H
