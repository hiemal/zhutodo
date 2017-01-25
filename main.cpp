#include <iostream>

#include "core.h"

int main() {

	Manager mainManager("main");


	std::string fpath = "../tasks.txt";
	mainManager.loadTasksFromFile(fpath);
	TaskContainer undonetsk = mainManager.getUndoneTasks();

	Task t("Test with space.");
	t.setDDL("2017-01-27");
	mainManager.addTask(t);

	TaskContainer todos = mainManager.getAllTasks();
	for (auto t:todos){
		std::cout << t.toString() << std::endl;
	}

	mainManager.writeTasksToFile(fpath);

	return 0;
}