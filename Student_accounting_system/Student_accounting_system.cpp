#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Student
{
public:
    string name;
    int age;
    vector <int>grades;

    double calculateAverage()
    {
        double sumgrd = 0.0;
        for (double grd : grades)
        {
            sumgrd += grd;
        }
        return sumgrd / grades.size();
    }

    void addGrade(int grade)
    {
        if (grade >= 1 && grade <= 5)
        {
            grades.push_back(grade);
        }
    }

    void displayInfo()
    {
        cout << "Студент: " << name << endl;
        cout << "Возраст: " << age << endl;
        cout << "Оценки: ";
        for (int grad : grades)
        {
            cout << grad << " ";
        }
        cout << endl << "Средний балл: " << calculateAverage() << endl << "---" << endl;
    }

};



int main()
{
    
}

