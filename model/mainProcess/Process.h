//
// Created by Artur Gubanovich on 19.12.22.
//

#ifndef BAZASTUDENTOWV2_PROCESS_H
#define BAZASTUDENTOWV2_PROCESS_H

#include "../student/StudentManager.h"
#include "../../view/ConsoleManager.h"

//Singletoon klasa z główną logiką programu
class Process {
private:
    // link do pliku ze studentami
    string filePath;

    //Prywatny konstruktor zapobiegający powstawaniu instancji
    Process() {}

    //Konstruktor kopiowania i operator przypisania są prywatne, aby zapobiec kopiowaniu
    Process(const Process &) = delete;

    Process &operator=(const Process &) = delete;

public:
    // Metoda statyczna, aby uzyskać jedyną instancję klasy
    static Process &getInstance() {
        static Process instance;
        return instance;
    }


    void setFilePath(string filePath) {
        this->filePath = filePath;
    }

//    główna petla programu
    int startSession() {

        StudentManager studentManager;
        studentManager.setFilePath(filePath);

        ConsoleManager consoleManager;

        while (true) {

            int index = consoleManager.printMenu();

            if (index == 1) {
                studentManager.printData();
            } else if (index == 2) {
                studentManager.addStudent();
            } else if (index == 3) {
                studentManager.removeStudent();
            } else if (index == 4) {

                int sortTarget = consoleManager.getSortTarget();

                int sortCrit = consoleManager.getSortCrit();

                if (sortTarget == 1) {

                    if (sortCrit == 1) {
                        studentManager.sortStudents(AVERAGE_ASSES, ASCENDING);
                    } else if (sortCrit == 2) {
                        studentManager.sortStudents(AVERAGE_ASSES, DESCENDING);
                    }

                } else if (sortTarget == 2) {

                    if (sortCrit == 1) {
                        studentManager.sortStudents(SURNAME, ASCENDING);
                    } else if (sortCrit == 2) {
                        studentManager.sortStudents(SURNAME, DESCENDING);
                    }

                }
            } else if (index == 5) {
                studentManager.changeDataStudent();
            } else if (index == 6) {
                return 0;
            } else {
                consoleManager.printError("niepoprawny index");
            }
        }
    }
};

#endif //BAZASTUDENTOWV2_PROCESS_H
