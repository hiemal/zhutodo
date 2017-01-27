# Zhutodo

## Incentives
There is no light todo app like Apple's reminder on Linux platform. Several existing apps contain too much useless functionalities like sync, timer, etc.. 

## Requirements
C++ 11. 

## Instructions
Run `build.sh` to build. The tasks will be saved/loaded from "tasks.txt" in the same folder.

 - q: quit
 - s: save to file
 - sd: set task to done
 - sud: set task to undone
 - rm: delete task
 - add: add new task

## Examples:
```
id |                              description |   createTime |          ddl |  status
---------------------------------------------------------------------------------------
 0 |                                     oink |   2017-01-26 |         None |  Undone
 1 |                                   sample |   2017-01-27 |   2017-02-01 |  Undone
---------------------------------------------------------------------------------------
```