cmake_minimum_required(VERSION 3.21)
project(BazaStudentowV2)

set(CMAKE_CXX_STANDARD 14)

add_executable(BazaStudentowV2 model/mainProcess/main.cpp model/student/StudentManager.h model/student/Student.h model/student/TypeOfSortingOfStudents.h model/mainProcess/Process.h model/initialization/Initialization.h view/ConsoleManager.h)
