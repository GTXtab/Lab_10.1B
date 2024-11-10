#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
using namespace std;

enum Specialnist { KN, INF, ME, FI, TN };  // KN - ����'������ �����, INF - �����������, ME - ���������� �� ��������, FI - Գ���� �� �����������, TN - ������� ��������
string specialnistStr[] = { "����'������ �����", "�����������", "���������� �� ��������", "Գ���� �� �����������", "������� ��������" };

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
    cout << "������ ������� ��������: "; cin >> N;

    Student* s = new Student[N];
    Create(s, N);
    Print(s, N);

    // ������ ���������� �������
    PrintStudentWithMinAverage(s, N);
    CountSatisfactoryGrades(s, N);

    delete[] s;
    return 0;
}

void Create(Student* s, const int N) {
    int specialnist;
    for (int i = 0; i < N; i++) {
        cout << "������� � " << i + 1 << ":" << endl;
        cin.get();
        cout << " �������: "; getline(cin, s[i].prizv);
        cout << " ����: "; cin >> s[i].kurs;
        cout << " ������������� (0 - ����'������ �����, 1 - �����������, 2 - ���������� �� ��������, 3 - Գ���� �� �����������, 4 - ������� ��������): ";
        cin >> specialnist;
        s[i].specialnist = (Specialnist)specialnist;
        cout << " ������ � ������: "; cin >> s[i].ocinkaFizyka;
        cout << " ������ � ����������: "; cin >> s[i].ocinkaMatematika;

        // �������� ������ ������ ������� �� ������������
        if (s[i].specialnist == KN) {
            cout << " ������ � �������������: "; cin >> s[i].ocinkaProgramming;
        }
        else if (s[i].specialnist == INF) {
            cout << " ������ � ��������� ������: "; cin >> s[i].ocinkaNumericalMethods;
        }
        else {
            cout << " ������ � ���������: "; cin >> s[i].ocinkaPedagogics;
        }
        cout << endl;
    }
}

void Print(const Student* s, const int N) {
    cout << "==================================================================================================================================" << endl;
    cout << "| � | �������           | ���� | �������������             | Գ���� | ���������� | ������������� | �������� ������ | ��������� |" << endl;
    cout << "----------------------------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++) {
        cout << "|" << setw(2) << right << i + 1
            << " | " << setw(18) << left << s[i].prizv
            << " | " << setw(4) << s[i].kurs
            << " | " << setw(25) << left << specialnistStr[s[i].specialnist]
            << " | " << setw(6) << s[i].ocinkaFizyka
            << " | " << setw(10) << s[i].ocinkaMatematika;

        // ��������� ������ ������ �������� �� ������������
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
        else {  // ��� ����� ��������������, ������� "���������� �� ��������", "Գ���� �� �����������" �� "������� ��������"
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
    cout << "������� � ��������� �������� �����: " << s[minIndex].prizv << endl;
}

void CountSatisfactoryGrades(const Student* s, const int N) {
    int satisfactoryPhysics = 0, satisfactoryMath = 0, satisfactoryInformatics = 0;

    for (int i = 0; i < N; i++) {
        if (s[i].ocinkaFizyka == 3) satisfactoryPhysics++;
        if (s[i].ocinkaMatematika == 3) satisfactoryMath++;

        // �������� ������ �� �������������
        if (s[i].specialnist == KN && s[i].ocinkaProgramming == 3) satisfactoryInformatics++;
        else if (s[i].specialnist == INF && s[i].ocinkaNumericalMethods == 3) satisfactoryInformatics++;
        else if (s[i].specialnist != KN && s[i].specialnist != INF && s[i].ocinkaPedagogics == 3) satisfactoryInformatics++;
    }

    cout << "ʳ������ ������ '���������' � ������: " << satisfactoryPhysics << endl;
    cout << "ʳ������ ������ '���������' � ����������: " << satisfactoryMath << endl;
    cout << "ʳ������ ������ '���������' � �����������: " << satisfactoryInformatics << endl;
}