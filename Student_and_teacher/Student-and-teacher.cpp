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

	virtual Person* clone() const = 0;
	virtual ~Person() = default;

	string getName() { return name; }
	int getAge() { return age; }
	string getEmail() { return email; }
	virtual string getRole() const = 0;

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
		cout << "Роль: " << getRole() << endl;
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
	Student(const Student& other) = default;
	Person* clone() const override { return new Student(*this); }

	string getStudentId() const { return studentId; }
	vector<int> getGrades() const { return grades; }
	string getRole() const override
	{
		return "Студент";
	}

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
	Teacher(const Teacher& other) = default;
	Person* clone() const override { return new Teacher(*this); }

	string getTeacherId() { return teacherId; }
	string getSubject() { return subject; }
	int getSalary() { return salary; }
	string getRole() const override
	{
		return "Преподаватель";
	}

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

class Administrator : public Person
{
private:
	string admId;
	string department;

public:

	Administrator() {}
	Administrator(string n, int a, string e, string i, string d)
		: Person(n, a, e),
		admId(i.empty() ? "Unknown" : i),
		department(d.empty() ? "Unknown" : d)
	{}
	Administrator(const Administrator& other) = default;
	Person* clone() const override { return new Administrator(*this); }

	string getAdmId() { return admId; }
	string getDepartment() { return department; }
	string getRole() const override { return "Админ"; }

	void setAdmId(string nai)
	{
		if (!nai.empty())
		{
			admId = nai;
		}
	}
	void setDepartment(string nd)
	{
		if (!nd.empty())
		{
			department = nd;
		}
	}

	void displayInfo() override
	{
		Person::displayInfo();
		cout << "ID: " << admId << endl << "Департамент: " << department << endl << "-----" << endl;
	}

};

class Researcher : public Person
{
private:
	string resId;
	string researchArea;
	int publications;

public:
	Researcher() {}
	Researcher(string n, int a, string e, string i, string r, int p)
		: Person(n, a, e),
		resId(i.empty() ? "Unknown" : i),
		researchArea(r.empty() ? "Unknown" : r),
		publications(p >= 0 ? p : 0)
	{}
	Researcher(const Researcher& other) = default;
	Person* clone() const override { return new Researcher(*this); }

	string getResId() { return resId; }
	string getResearchArea() { return researchArea; }
	int getPublications() { return publications; }
	string getRole() const override { return "Исследователь"; }

	void setResId(string nri)
	{
		if (!nri.empty())
		{
			resId = nri;
		}
	}
	void setResearchArea(string nra)
	{
		if (!nra.empty())
		{
			researchArea = nra;
		}
	}
	void setPublications(int np)
	{
		if (np>=0)
		{
			publications = np;
		}
	}

	void displayInfo() override
	{
		Person::displayInfo();
		cout << "ID: " << resId << endl << "Область исследования: " << researchArea << endl << "-----" << endl;
	}
};





int main()
{
	setlocale(LC_ALL, "ru");
	
	
	
}

