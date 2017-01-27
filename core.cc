#include "core.h"

#include <sstream>
#include <fstream>
#include <set>
#include <iomanip>

Task::Task(std::string desc)
{
    this->description = desc;
    this->deadline = "Unset";
    this->isDone = false;

    // use now time as create time
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, 80, "%Y-%m-%d", timeinfo);
    std::string str(buffer);
    this->createTime = str;
}

std::string Task::toString()
{
    std::stringstream ss;
    std::string done;
    if (this->isDone)
    {
	done = "Done";
    }
    else
    {
	done = "Undone";
    }
    std::string ddl = this->deadline;
    if (this->deadline == "0")
    {
	ddl = "None";
    }
    ss << std::setw(2) << uid << " | " << std::setw(40) << this->description << " | " << std::setw(12) << this->createTime << " | " << std::setw(12) << ddl << " | " << std::setw(7) << done;
    return ss.str();
}

std::string Task::toFile()
{
    std::stringstream ss;
    ss << this->description << "|" << this->createTime << "|" << this->deadline << "|" << this->isDone;
    return ss.str();
}

Manager::Manager(std::string n)
{
    this->name = n;
    this->programRun = true;
    this->fpath = "tasks.txt";
}

bool Manager::isOperationLegal(std::string s)
{
    if (s == "q" || s == "s" || s == "sd" || s == "sud" || s == "rm" || s == "add")
    {
	return true;
    }
    std::cout << "Illegal input. ";
    showHelp();
    return false;
}

void Manager::mainLoop()
{
    while (this->programRun)
    {
	showAllTasks();
	std::cout << "type your action:" << std::endl;
	std::string userInput;
	std::cin >> userInput;
	if (!isOperationLegal(userInput))
	{
	    continue;
	}
	handleUserInput(userInput);
    }
    return;
}

void Manager::showHelp()
{
    std::cout << "q:quit, s:save, sd:setdone, sud:setundone, rm:remove, add:add" << std::endl;
}

void Manager::handleUserInput(std::string s)
{
    if (s == "q")
    {
	this->programRun = false;
	writeTasksToFile();
    }
    if (s == "s")
    {
	// save file
	writeTasksToFile();
    }
    if (s == "sd")
    {
	// read index of task, set done
	int uid;
	std::cout << "type uid of task to set done:" << std::endl;
	std::cin >> uid;
	for (auto &t : this->allTasks)
	{
	    if (t.uid == uid)
	    {
		t.setDone(true);
		break;
	    }
	}
    }
    if (s == "sud")
    {
	// read index of task, set undone
	int uid;
	std::cout << "type uid of task to set undone:" << std::endl;
	std::cin >> uid;
	for (auto &t : this->allTasks)
	{
	    if (t.uid == uid)
	    {
		t.setDone(false);
		break;
	    }
	}
    }
    if (s == "rm")
    {
	// read index of task, remove it
	int uid;
	std::cout << "type uid of task to remove:" << std::endl;
	std::cin >> uid;
	int index = 0;
	for (auto &t : this->allTasks)
	{
	    if (t.uid == uid)
	    {
		break;
	    }
	    index++;
	}
	this->allTasks.erase(this->allTasks.begin() + index);
    }
    if (s == "add")
    {
	//add new task
	std::cout << "type task description:" << std::endl;
	std::string desc;
	std::cin >> desc;
	Task t(desc);
	std::cout << "type deadline (0 for no deadline): " << std::endl;
	zhutime ddl;
	std::cin >> ddl;
	t.setDDL(ddl);
	int uid;
	std::cout << "type uid:" << std::endl;
	std::cin >> uid;
	t.uid = uid;
	addTask(t);
    }

    return;
}

void Manager::addTask(Task task)
{
    allTasks.push_back(task);
}

TaskContainer Manager::getAllTasks()
{
    return allTasks;
}

TaskContainer Manager::getDoneTasks()
{
    TaskContainer doneTasks;
    for (auto &t : allTasks)
    {
	if (t.done())
	{
	    doneTasks.push_back(t);
	}
    }
    return doneTasks;
}

void Manager::loadTasksFromFile()
{
    std::string fname = this->fpath;
    std::string line;
    std::string ol;
    int linecounter = 0;
    std::ifstream inputFile(fname.c_str());
    if (inputFile.is_open())
    {
	std::string token;
	while (inputFile.good())
	{
	    getline(inputFile, line);
	    if (line.length() == 0)
		continue;
	    ol = line;

	    size_t pos = line.find("|", 0);
	    std::string desc = line.substr(0, pos).c_str();
	    line.erase(0, pos + 1);

	    pos = line.find("|", 0);
	    std::string ct = line.substr(0, pos).c_str();
	    line.erase(0, pos + 1);

	    pos = line.find("|", 0);
	    std::string ddl = line.substr(0, pos).c_str();
	    line.erase(0, pos + 1);

	    pos = line.find("|", 0);
	    bool isDone = ::atoi(line.substr(0, pos).c_str());
	    line.erase(0, pos + 1);

	    Task t(desc);
	    t.setDDL(ddl);
	    t.setCreateTime(ct);
	    t.setDone(isDone);
	    t.uid = linecounter;

	    //			std::cout << "Parser: " << t.toString() << std::endl;

	    this->allTasks.push_back(t);

	    linecounter++;
	}
    }
    //	std::cout << linecounter << " lines parsed" << std::endl;
}

void Manager::writeTasksToFile()
{
    std::string fname = this->fpath;
    std::ofstream f(fname);
    for (auto &t : this->allTasks)
    {
	f << t.toFile() << std::endl;
    }
    std::cout << "Tasks saved to " << fname << std::endl;
}

void Manager::showAllTasks()
{
    std::cout << std::setw(2) << "id"
	      << " | " << std::setw(40) << "description"
	      << " | " << std::setw(12) << "createTime"
	      << " | " << std::setw(12) << "ddl"
	      << " | " << std::setw(7) << "status" << std::endl;
    std::cout << "---------------------------------------------------------------------------------------" << std::endl;
    for (auto &task : this->allTasks)
    {
	std::cout << task.toString() << std::endl;
    }
    std::cout << "---------------------------------------------------------------------------------------" << std::endl;
}

TaskContainer Manager::getUndoneTasks()
{
    // TODO - should use reference
    TaskContainer udtsk;
    for (auto &t : allTasks)
    {
	if (!t.done())
	{
	    udtsk.push_back(t);
	}
    }
    this->undoneTasks = udtsk;
    return this->undoneTasks;
}
