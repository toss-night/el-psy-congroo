#include <iostream>
#include <vector>
#include <string>

class Task
{
private:
	bool done{ false };
	std::string taskName;

public:
	Task() : taskName("unknown") {}

	Task(std::string nameTask) 
		:taskName(!nameTask.empty() ? nameTask : "unknown")
	{}

	std::string getTaskName() const { return taskName; }

	bool getDone() const { return done; }

	void setTaskName(std::string&& name)
	{
		if (!name.empty())
		{
			taskName = name;
		}
	}

	void setDone(bool d)
	{
		done = d;
	}
};

class TaskList
{
private:
	std::vector<Task>tasks;	

public:
	TaskList() {}
	
	void addTask(std::string&& tas)
	{				
		tasks.push_back(Task (tas));
	}

	void showAllTasks() const
	{
		for (const auto& task : tasks)
		{
			std::cout << "[" << std::string(task.getDone() ? "X" : " ") << "] " << task.getTaskName() << "\n";
		}
	}

	void completeTask(const std::string& taskName)
	{
		auto it = find_if(tasks.begin(), tasks.end(), [&taskName](Task& task)
			{ return task.getTaskName() == taskName; });
		if (it != tasks.end())
		{
			it->setDone(true);
		}
		else
		{
			std::cout << "task not found!\n";
		}
	}

	void removeTask(const std::string& taskName)
	{
		auto it = find_if(tasks.begin(), tasks.end(), [&taskName](Task& task)
			{ return task.getTaskName() == taskName; });
		if (it != tasks.end())
		{
			tasks.erase(it);
		}
		else
		{
			std::cout << "task not found!\n";
		}
	}


};

int main()
{

}

