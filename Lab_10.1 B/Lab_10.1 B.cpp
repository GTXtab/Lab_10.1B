#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
using namespace std;

enum Specialnist { KN, INF, ME, FI, TN };  // KN - Комп'ютерні науки, INF - Інформатика, ME - Математика та економіка, FI - Фізика та інформатика, TN - Трудове навчання
string specialnistStr[] = { "Комп'ютерні науки", "Інформатика", "Математика та економіка", "Фізика та інформатика", "Трудове навчання" };

struct Student {
    string prizv;
    unsigned kurs;
    Specialnist specialnist;
    int ocinkaFizyka;
    int ocinkaMatematika;

    union {
        int ocinkaProgramming;
        int ocinkaNumericalMethods;
        int ocinkaPedagogics;
    };
};

void Create(Student* s, const int N);
void Print(const Student* s, const int N);

int FindStudentWithMinAverage(const Student* s, const int N);
void PrintStudentWithMinAverage(const Student* s, const int N);
void CountSatisfactoryGrades(const Student* s, const int N);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Введіть кількість студентів: "; cin >> N;

    Student* s = new Student[N];
    Create(s, N);
    Print(s, N);

    // Виклик додаткових функцій
    PrintStudentWithMinAverage(s, N);
    CountSatisfactoryGrades(s, N);

    delete[] s;
    return 0;
}

void Create(Student* s, const int N) {
    int specialnist;
    for (int i = 0; i < N; i++) {
        cout << "Студент № " << i + 1 << ":" << endl;
        cin.get();
        cout << " прізвище: "; getline(cin, s[i].prizv);
        cout << " курс: "; cin >> s[i].kurs;
        cout << " спеціальність (0 - Комп'ютерні науки, 1 - Інформатика, 2 - Математика та економіка, 3 - Фізика та інформатика, 4 - Трудове навчання): ";
        cin >> specialnist;
        s[i].specialnist = (Specialnist)specialnist;
        cout << " оцінка з фізики: "; cin >> s[i].ocinkaFizyka;
        cout << " оцінка з математики: "; cin >> s[i].ocinkaMatematika;

        // Введення третьої оцінки залежно від спеціальності
        if (s[i].specialnist == KN) {
            cout << " оцінка з програмування: "; cin >> s[i].ocinkaProgramming;
        }
        else if (s[i].specialnist == INF) {
            cout << " оцінка з чисельних методів: "; cin >> s[i].ocinkaNumericalMethods;
        }
        else {
            cout << " оцінка з педагогіки: "; cin >> s[i].ocinkaPedagogics;
        }
        cout << endl;
    }
}

void Print(const Student* s, const int N) {
    cout << "==================================================================================================================================" << endl;
    cout << "| № | Прізвище           | Курс | Спеціальність             | Фізика | Математика | Програмування | Чисельні методи | Педагогіка |" << endl;
    cout << "----------------------------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++) {
        cout << "|" << setw(2) << right << i + 1
            << " | " << setw(18) << left << s[i].prizv
            << " | " << setw(4) << s[i].kurs
            << " | " << setw(25) << left << specialnistStr[s[i].specialnist]
            << " | " << setw(6) << s[i].ocinkaFizyka
            << " | " << setw(10) << s[i].ocinkaMatematika;

        // Виведення третьої оцінки відповідно до спеціальності
        if (s[i].specialnist == KN) {
            cout << " | " << setw(13) << s[i].ocinkaProgramming
                << " | " << setw(15) << "-"
                << " | " << setw(10) << "-" << " |" << endl;
        }
        else if (s[i].specialnist == INF) {
            cout << " | " << setw(13) << "-"
                << " | " << setw(15) << s[i].ocinkaNumericalMethods
                << " | " << setw(10) << "-" << " |" << endl;
        }
        else {  // для інших спеціальностей, зокрема "Математика та економіка", "Фізика та інформатика" та "Трудове навчання"
            cout << " | " << setw(13) << "-"
                << " | " << setw(15) << "-"
                << " | " << setw(10) << s[i].ocinkaPedagogics << " |" << endl;
        }
    }
    cout << "==================================================================================================================================" << endl;
}

int FindStudentWithMinAverage(const Student* s, const int N) {
    int minIndex = 0;
    double minAvg = (s[0].ocinkaFizyka + s[0].ocinkaMatematika + (s[0].specialnist == KN ? s[0].ocinkaProgramming :
        (s[0].specialnist == INF ? s[0].ocinkaNumericalMethods : s[0].ocinkaPedagogics))) / 3.0;

    for (int i = 1; i < N; i++) {
        double avg = (s[i].ocinkaFizyka + s[i].ocinkaMatematika + (s[i].specialnist == KN ? s[i].ocinkaProgramming :
            (s[i].specialnist == INF ? s[i].ocinkaNumericalMethods : s[i].ocinkaPedagogics))) / 3.0;
        if (avg < minAvg) {
            minAvg = avg;
            minIndex = i;
        }
    }
    return minIndex;
}

void PrintStudentWithMinAverage(const Student* s, const int N) {
    int minIndex = FindStudentWithMinAverage(s, N);
    cout << "Студент з найменшим середнім балом: " << s[minIndex].prizv << endl;
}

void CountSatisfactoryGrades(const Student* s, const int N) {
    int satisfactoryPhysics = 0, satisfactoryMath = 0, satisfactoryInformatics = 0;

    for (int i = 0; i < N; i++) {
        if (s[i].ocinkaFizyka == 3) satisfactoryPhysics++;
        if (s[i].ocinkaMatematika == 3) satisfactoryMath++;

        // Перевірка оцінки за спеціальністю
        if (s[i].specialnist == KN && s[i].ocinkaProgramming == 3) satisfactoryInformatics++;
        else if (s[i].specialnist == INF && s[i].ocinkaNumericalMethods == 3) satisfactoryInformatics++;
        else if (s[i].specialnist != KN && s[i].specialnist != INF && s[i].ocinkaPedagogics == 3) satisfactoryInformatics++;
    }

    cout << "Кількість оцінок 'задовільно' з фізики: " << satisfactoryPhysics << endl;
    cout << "Кількість оцінок 'задовільно' з математики: " << satisfactoryMath << endl;
    cout << "Кількість оцінок 'задовільно' з інформатики: " << satisfactoryInformatics << endl;
}
