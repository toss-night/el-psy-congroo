#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Person
{
private:
	string name;
	int age;
	string email;
public:

	Person() {}
	Person(string nname, int nage, string nemail)
		:name(nname.empty() ? "Unknown" : nname),
		age(nage >= 16 ? nage : 0),
		email(nemail.find("@edu.ru") != string::npos ? nemail : "Unknown")
	{}

	string getName() { return name; }
	int getAge() { return age; }
	string getEmail() { return email; }

	void setName(string nname)
	{
		if (!nname.empty())
		{
			name = nname;
		}
	}
	void setAge(int nage)
	{
		if (nage >= 16)
		{
			age = nage;
		}
	}
	void setEmail(string nemail)
	{
		if (nemail.find("@edu.ru") != string::npos && !nemail.empty())
		{
			email = nemail;
		}
	}

	virtual void displayInfo()
	{
		cout << "Имя: " << name << endl << "Возраст: " << age << endl;
		cout << "Почта: " << email << endl;
	}

};

class Student : public Person
{
private:
	string studentId;
	vector <int> grades;

public:

	Student(){}
	Student(string nname, int nage, string nemail, string nstudentId, vector<int>ngrades)
		: Person(nname, nage, nemail),
		studentId(nstudentId.empty() ? "Unknown" : nstudentId)
	{
		for (int grade:ngrades)
		{
			if (grade >= 1 && grade <= 5)
			{
				grades.push_back(grade);
			}
		}	
	}

	string getStudentId() const { return studentId; }
	vector<int> getGrades() const { return grades; }

	void setStudentId(string nstudentId)
	{
		if (!nstudentId.empty())
		{
			studentId = nstudentId;
		}
	}
	void setGrades(vector <int> ngrades)
	{
		for (int grade : ngrades)
		{
			if (grade >= 1 && grade <= 5)
			{
				grades.push_back(grade);
			}
		}
	}

	double calculateAverage()
	{
		if (grades.empty())
		{
			return 0.0;
		}
		else
		{
			double avegrd = 0.0;
			for (double grade : grades)
			{
				avegrd += grade;
			}
			return avegrd/grades.size();
		}
	}

	void displayInfo() override
	{
		Person::displayInfo();
		cout << "ID: " << studentId << endl<<"Оценки: ";
		for (int grade : grades)
		{
			cout << grade << " ";
		}
		cout << endl << "Средняя оценка: " << calculateAverage() << endl;
		cout << endl << "-----" << endl;
	}
};

class Teacher : public Person
{
private:
	string teacherId;
	string subject;
	int salary;

public:
	Teacher(){}
	Teacher(string nname, int nage, string nemail, string nteacherId, string nsubject, int nsalary)
		: Person(nname, nage, nemail),
		teacherId(!nteacherId.empty() ? nteacherId : "Unknown"),
		subject(!nsubject.empty() ? nsubject : "Unknown"),
		salary(nsalary >= 0 ? nsalary : 0)
	{}

	string getTeacherId() { return teacherId; }
	string getSubject() { return subject; }
	int getSalary() { return salary; }

	void setTeacherId(string nteacherId)
	{
		if (!nteacherId.empty())
		{
			teacherId = nteacherId;
		}
	}
	void setSubject(string nsubject)
	{
		if (!nsubject.empty())
		{
			subject = nsubject;
		}
	}
	void setSalary(int nsalary)
	{
		if (nsalary>=0)
		{
			salary = nsalary;
		}
	}	

	void displayInfo() override
	{
		Person::displayInfo();
		cout << "ID: " << teacherId << endl << "Предмет: " << subject << endl;
		cout << "Зарплата: " << salary << " рублей в месяц" << endl << "-----" << endl;
	}
};


int main()
{
	
}

