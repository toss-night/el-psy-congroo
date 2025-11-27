#include <iostream>
#include <vector>
#include <string>

class TaskList
{
private:
	struct Task
	{	
		bool done{ false };
		std::string taskName;
	
		Task() : taskName("unknown") {}
		Task(const std::string& nameTask)
			:taskName(!nameTask.empty() ? nameTask : "unknown")
		{}	
	};

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
			std::cout << "[" << std::string(task.done ? "X" : " ") << "] " << task.taskName << "\n";
		}
	}

	void completeTask(const std::string& ntaskName)
	{
		auto it = std::find_if(tasks.begin(), tasks.end(), [&ntaskName](Task& task)
			{ return task.taskName == ntaskName; });
		if (it != tasks.end())
		{
			it->done = true;
		}
		else
		{
			std::cout << "task not found!\n";
		}
	}

	void removeTask(const std::string& ntaskName)
	{
		auto it = std::find_if(tasks.begin(), tasks.end(), [&ntaskName](Task& task)
			{ return task.taskName == ntaskName; });
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

