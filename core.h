#ifndef CORE_H
#define CORE_H

#include <string>
#include <vector>
#include <ctime>
#include <iostream>

#include <unistd.h>
#include <term.h>

typedef std::string zhutime;

class Task
{

  public:
    Task(std::string);

    std::string getDesc()
    {
	return this->description;
    }

    void setDDL(zhutime t)
    {
	this->deadline = t;
    }

    zhutime getDDL()
    {
	return this->deadline;
    }

    zhutime getCreateTime()
    {
	return this->createTime;
    }

    void setCreateTime(zhutime t)
    {
	this->createTime = t;
    }

    void setDone(bool b)
    {
	this->isDone = b;
    }

    bool done()
    {
	return this->isDone;
    }

    std::string toString();
    std::string toFile(); // toString without UID

    int uid;

  protected:
    std::string description;
    zhutime deadline, createTime;
    bool isDone;
};

typedef std::vector<Task> TaskContainer;

class Manager
{
  public:
    Manager(std::string);
    TaskContainer getAllTasks();
    TaskContainer getUndoneTasks();
    TaskContainer getDoneTasks();
    void showAllTasks();

    void loadTasksFromFile();
    void writeTasksToFile();

    void addTask(Task);

    void showHelp();

    // user manipulation
    void mainLoop();

  protected:
    bool isOperationLegal(std::string);
    void handleUserInput(std::string);

    std::string fpath;
    std::string name;
    TaskContainer allTasks, undoneTasks;
    bool programRun;
};

#endif