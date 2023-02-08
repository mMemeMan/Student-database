//
// Created by Artur Gubanovich on 18.12.22.
//

#ifndef BAZASTUDENTOWV2_STUDENT_H
#define BAZASTUDENTOWV2_STUDENT_H

#include <string>

using namespace std;

static const int NAME_SIZE = 40;
static const int SURNAME_SIZE = 50;
static const int ADRES_SIZE = 80;
static const int СOURSE_STUDY_SIZE = 40;

struct Student {
    char *name = new char[NAME_SIZE];
    char *surname = new char[SURNAME_SIZE];
    short academicYear;
    char *courseOfStudy = new char[СOURSE_STUDY_SIZE];
    char *adres = new char[ADRES_SIZE];
    double averageOfAssessments;
};


#endif //BAZASTUDENTOWV2_STUDENT_H
