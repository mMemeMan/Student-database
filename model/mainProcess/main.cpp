#include <algorithm>
#include "Process.h"
#include "../initialization/Initialization.h"

//Warjant 10
//Dany jest plik zawierający dane studentów:
//imię, nazwisko, rok_studiów, kierunek, adres, średniaz ocen.
//Dane zapisane w pliku binarnym. Napisz program,
//który umożliwi dodanie danych nowego studenta,
//usunięcie danych, edycję a także posortowanie
//elementów pliku rosnąco lub malejąco (wybór użytkownika) wg. podanego kryterium.
//Podaj rozwiązanie bez tablic pomocniczych.

using namespace std;

//link do pliku ze studentami
const string filePath = "..\\..\\BazaStudentow.dat";

int main() {

//    inicjowanie danych startowych do pliku
    Initialization initialization;
    initialization.init(filePath);

//    uruchamianie głównej pętli
    Process& process = Process::getInstance();
    process.setFilePath(filePath);
    process.startSession();


    return 0;
}