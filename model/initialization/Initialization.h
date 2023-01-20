//
// Created by Artur Gubanovich on 19.12.22.
//

#ifndef BAZASTUDENTOWV2_INITIALIZATION_H
#define BAZASTUDENTOWV2_INITIALIZATION_H

#include "../student/Student.h"
#include <fstream>

class Initialization {

public:
//inicjowanie początkowych danych dla pliku BazaStudentow
void init(string filePath) {

    ofstream writer(filePath, ios::binary | ios::out);
    Student std1 = {"Artur", "Gubanovich", 1,
                    "informatyka", "ul zytnia 17/19", 6};
    Student std2 = {"SerGej", "Nadmennyj", 1,
                    "informatyka", "ul 3 maja", 4};
    Student std3 = {"Uladzislau", "Sok", 1,
                    "informatyka", "ul zytnia 17/19", 0};
    Student std4 = {"Kram", "Kudriakow", 1,
                    "turizm", "ul zytnia 17/19", 4};
    Student std5 = {"Igorъ", "Faldouskij", 1,
                    "informatyka", "ul. zytnia 17/19", 5};
    writer.write(reinterpret_cast<char *>(&std1), sizeof(std1));
    writer.write(reinterpret_cast<char *>(&std2), sizeof(std2));
    writer.write(reinterpret_cast<char *>(&std3), sizeof(std3));
    writer.write(reinterpret_cast<char *>(&std4), sizeof(std4));
    writer.write(reinterpret_cast<char *>(&std5), sizeof(std5));
    writer.close();
}
};

#endif //BAZASTUDENTOWV2_INITIALIZATION_H
