#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Student
{
private:
    string name;
    int age;
    vector <int>grades;

public:

    Student() {}
    Student(string nname, int nage, vector<int>ngrades)
    {
        if (!nname.empty())
        {
            name = nname;
        }
        if (nage >= 16 && nage <= 60)
        {
            age = nage;
        }
        bool grdsValid = false;
        for (int grade : ngrades)
        {
            if (grade <= 5 && grade >= 1)
            {
                grdsValid = true;
            }
        }
        if (grdsValid)
        {
            grades = ngrades;
        }
    }

    void setName(string nname)
    {
        if (!nname.empty())
        {
            name = nname;
        }
    }
    void setAge(int nage)
    {
        if (nage >= 16 && nage <= 60)
        {
            age = nage;
        }
    }
    
    string getName()
    {
        return name;
    }
    int getAge()
    {
        return age;
    }
    vector<int> getGrades()
    {
        return grades;
    }

    double calculateAverage()
    {
        double sumgrd = 0.0;
        for (double grd : grades)
        {
            sumgrd += grd;
        }
        if (grades.size() != 0)
        {
            return sumgrd / grades.size();
        }
        else
        {
            return 0.0;
        }
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
    setlocale(LC_ALL, "ru");
    
}

