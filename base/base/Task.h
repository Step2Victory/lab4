#pragma once
#include <string>
using namespace std;


class Task
{
	int time;
	int reqCores;
	string taskName;
public:
	Task(int t = 0);
	Task(int t, int r);
	Task(int t, int r, string name);
	Task operator--(int);
	bool isReady();
	int getCores()
	{
		return reqCores;
	}
	int getTime()
	{
		return time;
	}
	string getTaskName()
	{
		return taskName;
	}
	~Task();
};
Task::Task(int t)
{
	if (t < 0)
		throw 1;
	time = t;
	reqCores = 1;
	taskName = "";
}
Task::Task(int t, int r)
{
	if (t < 0 || r < 1)
		throw 1;
	time = t;
	reqCores = r;
	taskName = "";
}

Task::Task(int t, int r, string name)
{
	if (t < 0 || r < 1)
		throw 1;
	time = t;
	reqCores = r;
	taskName = name;
}

Task Task::operator--(int a)
{
	if (isReady())
		throw 1;
	Task b(time);
	time--;
	return b;
}

bool Task::isReady()
{
	if (time < 0)
		throw 1;
	if (time == 0)
		return true;
	return false;
}

Task::~Task()
{
}

