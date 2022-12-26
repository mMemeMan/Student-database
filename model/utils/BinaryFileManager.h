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
    T readElement(int position) {
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

//    Zamiana starego pliku na nowy
    void fileSubstitute(string filePath, string replacementFilePath) {
        char filePathChars[filePath.length()];
        strcpy(filePathChars, filePath.c_str());
        remove(filePathChars);

        char replacmentFPChars[replacementFilePath.length()];
        strcpy(replacmentFPChars, replacementFilePath.c_str());

        int result;
        result = rename(replacmentFPChars, filePathChars);
        if (result == 0) {
//            puts("File successfully renamed");
        } else {
            perror("Error renaming file");
            throw new exception;
        }
    }

    //    zmiana miejsc dwóch elementow w pliku
    void swapElements(int swapPoint) {
        char tempFileName[] = "sortedTempFile.dat";

        T t;
        T lastT;
        ifstream reader(filePath, ios::binary);
        ofstream writer(tempFileName, ios::binary | ios::out);

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

        fileSubstitute(filePath, tempFileName);
    }
};

#endif //BAZASTUDENTOWV2_BINARYFILEMANAGER_H
