#include "core.h"

#include <sstream>
#include <fstream>
#include <iostream>

Task::Task(std::string desc){
this->description = desc;
this->deadline = "Unset";
this->isDone = false;

// use now time as create time
time_t rawtime;
struct tm * timeinfo;
char buffer[80];

time (&rawtime);
timeinfo = localtime(&rawtime);

strftime(buffer,80,"%Y-%m-%d",timeinfo);
std::string str(buffer);
this->createTime = str;

}


std::string Task::toString() {
	std::stringstream ss;
	ss << this->description << "|" << this->createTime << "|" << this->deadline << "|" << this->isDone;
	return ss.str();
}










Manager::Manager(std::string n) {
	this->name = n;
}


void Manager::addTask(Task task) {
	allTasks.push_back(task);
}

TaskContainer Manager::getAllTasks() {
	return allTasks;
}

TaskContainer Manager::getDoneTasks() {
	TaskContainer doneTasks;
	for (auto & t:allTasks){
		if (t.done()){
			doneTasks.push_back(t);
		}
	}
	return doneTasks;
}

void Manager::loadTasksFromFile(std::string fname) {
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
			if (line.length() == 0) continue;
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

			std::cout << "Parser: " << t.toString() << std::endl;

			this->allTasks.push_back(t);

			linecounter++;
		}
	}
	std::cout << linecounter << " lines parsed" << std::endl;
}

void Manager::writeTasksToFile(std::string fname) {
	std::ofstream f(fname);
	for (auto t:this->allTasks){
		f << t.toString() << std::endl;
		std::cout << "Write task " << t.getDesc() << std::endl;
	}
}


TaskContainer Manager::getUndoneTasks() {
	// TODO - should use reference
	TaskContainer udtsk;
	for (auto t:allTasks){
		if (!t.done()) {
			udtsk.push_back(t);
		}
	}
	this->undoneTasks = udtsk;
	return this->undoneTasks;
}