#ifndef CORE_H
#define CORE_H

#include <string>
#include <vector>

#include <ctime>



typedef std::string zhutime;

class Task{

public:
Task(std::string);

std::string getDesc(){
	return this->description;
}

void setDDL(zhutime t){
	this->deadline = t;
}

zhutime getDDL(){
	return this->deadline;
}

zhutime getCreateTime(){
	return this->createTime;
}

void setCreateTime(zhutime t){
	this->createTime = t;
}

void setDone(bool b){
	this->isDone = b;
}

bool done(){
	return this->isDone;
}

std::string toString();

protected:
std::string description;
zhutime deadline, createTime;
bool isDone;

};


typedef std::vector<Task> TaskContainer;

class Manager{
public:
Manager(std::string);
TaskContainer getAllTasks();
TaskContainer getUndoneTasks();
TaskContainer getDoneTasks();

void loadTasksFromFile(std::string);
void writeTasksToFile(std::string);

void addTask(Task);

protected:
std::string name;
TaskContainer allTasks, undoneTasks;

};






#endif