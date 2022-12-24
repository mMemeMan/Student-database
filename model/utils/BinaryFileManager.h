//
// Created by Artur Gubanovich on 24.12.22.
//

#ifndef BAZASTUDENTOWV2_BINARYFILEMANAGER_H
#define BAZASTUDENTOWV2_BINARYFILEMANAGER_H

#include <iostream>
#include <string>
#include <fstream>
#include "../student/Student.h"

using namespace std;

template<class T>
class BinaryFileManager {

private:
    string filePath;

public:

    void setFilePath(string filePath) {
        this->filePath = filePath;
    }

    //    wynalizienie ostatniego indeksu w pliku
    int findLastIndexInBinaryFile() {
        T t;
        ifstream reader(filePath, ios::binary);
        int lastIndex;
        for (int i = 0;; i++) {
            reader.read(reinterpret_cast<char *>(&t), sizeof(t));
            if (reader.eof()) {
                lastIndex = i;
                break;
            }
        }
        reader.close();
        return lastIndex;
    }

    //    odczyt danych w określonym punkcie
    Student readStudent(int position) {
        T t;
        ifstream reader(filePath, ios::binary);
        for (int i = 0;; i++) {
            reader.read(reinterpret_cast<char *>(&t), sizeof(t));
            if (reader.eof()) break;
            if (i == position) return t;
        }
        reader.close();
        return t;
    }

    //    zmiana miejsc dwóch elementow w pliku
    void swapStudents(int swapPoint) {
        T t;
        T lastT;
        ifstream reader(filePath, ios::binary);
        ofstream writer("sortedTempFile.dat", ios::binary | ios::out);

        bool pointFinded = false;
        for (int i = 0;; i++) {
            reader.read(reinterpret_cast<char *>(&t), sizeof(t));
            if (reader.eof()) break;

            if (i == swapPoint) {
                lastT = t;
                pointFinded = true;
            } else if (pointFinded) {
                writer.write(reinterpret_cast<char *>(&t), sizeof(t));
                writer.write(reinterpret_cast<char *>(&lastT), sizeof(lastT));
                pointFinded = false;
            } else {
                writer.write(reinterpret_cast<char *>(&t), sizeof(t));
            }
        }
        reader.close();
        writer.close();

        char filePathChars[filePath.length()];
        strcpy(filePathChars, filePath.c_str());
        remove(filePathChars);

        char oldname[] = "sortedTempFile.dat";
        char newname[filePath.length()];
        for (int i = 0; i < filePath.length(); ++i) {
            newname[i] = filePath[i];
        }

        int result;
        result = rename(oldname, newname);
        if (result == 0) {
//            puts("File successfully renamed");
        } else {
            perror("Error renaming file");
            throw new exception;
        }
    }
};

#endif //BAZASTUDENTOWV2_BINARYFILEMANAGER_H
