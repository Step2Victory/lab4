#pragma once
#include "Task.h"
#include "Processor.h"
#include <iostream>

class Cluster
{
	Queue<Task> q;
	int nProc;
	int nClock;
	int maxCores;
	Processor* pMem;
	int busyCores;
	int allCores;
public:
	Cluster(vector<int> coreNumbers)
	{
		nProc = coreNumbers.size();
		if (nProc == 0)
			throw 1;
		pMem = new Processor[nProc];
		nClock = 0;
		busyCores = 0;
		maxCores = 0;
		allCores = 0;
		for (int i = 0; i < nProc; ++i)
		{
			if (coreNumbers[i] <= 0)
				throw 1;
			if (coreNumbers[i] > maxCores)
				maxCores = coreNumbers[i];
			Processor a(coreNumbers[i]);
			pMem[i] = a;
			allCores += coreNumbers[i];
		}
	}
	void addTasks(vector<Task>);
	void nextClock();
	double stat()
	{
		return double(busyCores) / (nClock * allCores);
	}
	void printStatistics(bool detail = false);
	~Cluster()
	{
		delete[]pMem;
	}
};


void Cluster::addTasks(vector<Task> tasks)
{
	for (auto task : tasks)
	{
		if (task.getCores() <= maxCores)
			q.push(task);
	}
		
}


void Cluster::nextClock()
{
	nClock++;
	bool canAddTask = true;
	for (int i = 0; i < nProc; ++i)
	{
		pMem[i].nextClock();
		pMem[i].delReadyTasks();
	}
	while (!q.isEmpty() && canAddTask)
	{
		canAddTask = false;
		for (int i = 0; i < nProc && !q.isEmpty(); ++i)
		{
			if (pMem[i].addTask(q.top()))
			{
				q.pop();
				canAddTask = true;
			}
				
		}
	}
	for (int i = 0; i < nProc; ++i)
	{
		busyCores += pMem[i].cores() - pMem[i].freeCores();
	}
}

void Cluster::printStatistics(bool detail)
{
	double all = 0, free = 0;
	for (int i = 0; i < nProc; ++i)
	{
		free += pMem[i].freeCores();
		all += pMem[i].cores();
	}
	cout << "Такт " << nClock << endl;
	cout << "Общая загрузка кластера: " << (all - free) / all * 100 << "%" << endl;
	if (detail)
	{
		cout << "Загрузка по процессорам: " << endl;
		for (int i = 0; i < nProc; ++i)
		{
			cout << "Процессор " << i + 1 << ": " << double(pMem[i].cores() - pMem[i].freeCores()) / pMem[i].cores() * 100 << "%";
			vector<string>names = pMem[i].taskNames();

			string ansNames = "(";
			for (auto name : names)
			{
				ansNames += name + ", ";
			}
				
			if (ansNames[ansNames.size() - 1] == ' ')
				ansNames = ansNames.erase(ansNames.size() - 2, 2);
			ansNames += ")";
			cout << ansNames << endl << "\t Занято ядер: " <<
				pMem[i].cores() - pMem[i].freeCores() << endl << "\t Всего ядер: " << pMem[i].cores() << endl;
		}
	}
}
