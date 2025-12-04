#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

class TaskList
{
private:
	struct Task
	{	
		bool done{ false };
		std::string taskName;
	
		Task() : taskName("unknown") {}
		Task(const std::string& nameTask, const bool& d = false)
			:taskName(!nameTask.empty() ? nameTask : "unknown"),
			done(d)
		{}		
		
	};

	std::vector<Task>tasks;	

public:
	TaskList() {}
	
	void addTask(const std::string& tas)
	{				
		tasks.push_back(Task (tas));
	}
	void addTask(const std::string& tas,const bool& don)
	{
		tasks.push_back(Task(tas,don));
	}
	void clearTasks()
	{
		tasks.clear();
	}
	auto findTask(const std::string& taskname) 
	{
		return std::find_if(tasks.begin(), tasks.end(), 
			[&taskname](Task& task) {return task.taskName == taskname; });		
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
		auto it = findTask(ntaskName);
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
		auto it = findTask(ntaskName);
		if (it!=tasks.end())
		{
			tasks.erase(it);
		}
		else
		{
			std::cout << "task not found!\n";
		}
	}
	void saveToFile(const std::string& filename)
	{
		std::ofstream file(filename);
		for (const auto& task : tasks)
		{
			file << "[" << std::string(task.done ? "X" : " ") << "] " << task.taskName << "\n";
		}
	}
	void loadFromFile(const std::string& filename)
	{
		std::string line;
		std::ifstream file(filename);

		if (!file.is_open())
		{
			std::cout << "cannot open file: " << filename << "\n";
			return;
		}
		while (getline(file, line))
		{							
			if (line.length()>=4&&line[0] == '[')
			{
				bool isDone = (line[1] == 'X');
				std::string task = line.substr(4);
				addTask(task, isDone);
			}								
		}
	}
	void editTask(const std::string& oldName, const std::string& newName)
	{
		auto it = findTask(oldName);
		if (it != tasks.end())
		{
			it->taskName = newName;
		}
		else
		{
			std::cout << "task not found!\n";
		}
	}
	void clearCompleted()
	{
		tasks.erase(std::remove_if(tasks.begin(), tasks.end(),
			[](const Task& task) {return task.done; }),tasks.end());
	}
	void markAllAsDone()
	{
		for (auto& task : tasks)
		{
			task.done = true;
		}
	}
	int getTotalCount()
	{
		return tasks.size();
	}
	int getCompletedCount() const
	{
		return std::count_if(tasks.begin(), tasks.end(), 
			[](const Task& task) { return task.done; });
	}
	int getPendingCount() const
	{
		return std::count_if(tasks.begin(), tasks.end(),
			[](const Task& task) { return !task.done; });
	}
	void showCompleted() const
	{		
		std::cout << "complited tasks: " << getCompletedCount() << "\n";
	}
	void showPending() const
	{		
		std::cout << "pending tasks: " << getPendingCount() << "\n";
	}
	void getCommand()
	{
		std::string com;		
		while(com!="exit")
		{
			
			std::cout << "\n";
			std::cout << "enter command(add, complete, remove, edit, search, save, load, stats, clear, exit): \n";			
			std::cin >> com;
			if (com == "add")
			{
				std::string task;
				std::cout << "enter task to add: ";
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::getline(std::cin,task);
				addTask(task);
							
			}
			else if (com == "complete")
			{
				std::string task;
				std::cout << "enter task to complete: ";
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::getline(std::cin, task);
				completeTask(task);
				
				
			}
			else if (com == "remove")
			{
				std::string task;
				std::cout << "enter task to remove: ";
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::getline(std::cin, task);
				removeTask(task);
				
				
			}
			else if (com == "edit")
			{
				std::string task, ntask;
				std::cout << "enter task to find: ";
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::getline(std::cin, task);
				std::cout << "enter new name for task: ";
				std::getline(std::cin, ntask);
				editTask(task, ntask);								
			}
			else if (com == "search")
			{
				std::string task;
				std::cout << "enter task to find: ";
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::getline(std::cin, task);
				auto it = std::find_if(tasks.begin(), tasks.end(), [&task](Task& tas) {return task == tas.taskName; });
				if (it != tasks.end())
				{
					std::cout << "this task " << (it->done ? "complited" : "not complited") << "!\n";
				}
				else
				{
					std::cout << "task not found!\n";
				}
				
				
			}
			else if (com == "save")
			{
				std::string file;
				std::cout << "enter file name for save all tasks: ";
				std::cin >> file;
				saveToFile(file);
				
				
			}
			else if (com == "load")
			{
				std::string file;
				std::cout << "enter file name for load all tasks: ";
				std::cin >> file;
				loadFromFile(file);
				
				
			}
			else if (com == "stats")
			{
				std::cout << "total tasks: " << getTotalCount() << "\n";
				showCompleted();
				showPending();
				std::cout << "tasks:\n";
				showAllTasks();
				
				
			}	
			else if (com == "clear")
			{				
				std::cout << "clear " << tasks.size() << " tasks\n";
				clearTasks();
				
			}
			else
			{
				std::cout << "command not found!\n";
				
				
			}
			
		}
	}
};



int main()
{
	
}