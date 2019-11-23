#pragma once
#include "task.h"
#include "Queue.h"
#include <vector>
#include <string>
using namespace std;


class Processor
{
	int nCores;
	int nFreeCores;
	Node<Task>* pFirstTask;
public:
	Processor(int n = 0)
	{
		pFirstTask = nullptr;
		nCores = n;
		nFreeCores = n;
	}
	bool isEmpty();
	void nextClock();
	void delReadyTasks();
	bool addTask(Task t);
	int freeCores()
	{
		return nFreeCores;
	}
	vector<string> taskNames();
	int cores()
	{
		return nCores;
	}
	~Processor();
};


bool Processor::isEmpty()
{
	if (nCores == nFreeCores)
		return true;
	return false;
}

void Processor::nextClock()
{
	Node<Task> *p = pFirstTask;
	while (p != nullptr)
	{
		(p->value)--;
		p = p->pNext;
	}
}

void Processor::delReadyTasks()
{
	if (isEmpty())
		return;
	Node<Task>*p1 = pFirstTask;
	Node<Task>*p2 = pFirstTask->pNext;
	while (p1 != nullptr && (p1->value).isReady())
	{
		nFreeCores += (p1->value).getCores();
		pFirstTask = p2;
		delete p1;
		p1 = p2;
		if (p2 != nullptr)
			p2 = p2->pNext;
	}
	while (p2 != nullptr)
	{
		if ((p2->value).isReady())
		{
			nFreeCores += (p2->value).getCores();
			p1->pNext = p2->pNext;
			delete p2;
			p2 = p1->pNext;
		}
		else
		{
			Node<Task>* tmp = p2;
			p2 = p2->pNext;
			p1 = tmp;
		}
	}
}

bool Processor::addTask(Task t)
{
	if (t.getCores() > nFreeCores)
		return false;
	nFreeCores -= t.getCores();
	Node<Task> *p = new Node<Task>;
	p->value = t;
	p->pNext = pFirstTask;
	pFirstTask = p;
	return true;
}

vector<string> Processor::taskNames()
{
	vector<string> ans;
	Node<Task>*p = pFirstTask;
	while (p != nullptr)
	{
		ans.push_back((p->value).getTaskName());
		p = p->pNext;
	}
	return ans;
}

Processor::~Processor()
{
	Node<Task>*p = pFirstTask;
	while (p != nullptr)
	{
		Node<Task>*tmp = p->pNext;
		delete p;
		p = tmp;
	}
}


