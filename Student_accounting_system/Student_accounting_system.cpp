#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
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

    double calculateAverage() const
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

class StudentGroup
{
private:
    vector<Student> students;

public:

    StudentGroup() {}
    StudentGroup(vector<Student> nstudents)
    {
        students = nstudents;
    }

    void addStudent(Student student)
    {
        students.push_back(student);
    }

    Student findStudentsByPartialName(string partial)
    {
        auto it = find_if(students.begin(), students.end(), [&partial](Student& st)
            {
                return st.getName().find(partial) != std::string::npos;

            });
        if (it != students.end())
        {
            return *it;
        }
        else
        {

            throw std::runtime_error("Студент не найден");
        }
    }

    Student findStudentByName(string name)
    {
        auto it = find_if(students.begin(), students.end(), [&name](Student& st) {return st.getName() == name; });
        if (it != students.end())
        {
            return *it;
        }
        else
        {

            throw std::runtime_error("Студент не найден");
        }
    }

    void sortByAverage()
    {
        sort(students.begin(), students.end(),
            [](const Student&  a, const Student& b) 
            {
                return a.calculateAverage() > b.calculateAverage();  
            });

    }

    void displayAllStudents()
    {
        for (Student stdnt : students)
        {
            stdnt.displayInfo();
        }
    }

    StudentGroup getTopStudents(int n)
    {
        vector<Student>topStudents;
        sortByAverage();
        int count = min(n, (int)students.size());
        for (int i = 0; i < count; i++)
        {
            topStudents.push_back(students[i]);
        }
        return topStudents;
    }
};


int main()
{
   
    
}


