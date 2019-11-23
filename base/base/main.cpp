// main.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include "Cluster.h"
#include "windows.h"
#include <ctime>
#include <iostream>
using namespace std;


void keyboard_input()
{
	cout << "Выводить статистику по загрузке каждого процессора? Y/N ";
	char a;
	bool flag = false;
	cin >> a;
	if (a == 'Y' || a == 'y')
		flag = true;
	int n;
	cout << "Введите кол-во процессоров: ";
	cin >> n;
	vector<int>pr(n);
	for (int i = 0; i < n; ++i)
	{
		cout << "Введите кол-во ядер для " << i << "-го процессора: ";
		cin >> pr[i];
	}
	cout << endl;
	Cluster cl(pr);
	int nClock;
	cout << "Введите кол-во тактов: ";
	cin >> nClock;
	int k = 0;
	for (int i = 0; i < nClock; ++i)
	{
		int nTasks;
		cout << "Введите кол-во задач на " << i << "-ом такте: ";
		cin >> nTasks;
		vector<Task> b;
		for (int j = 0; j < nTasks; ++j)
		{
			int time, req;
			string name = "task" + to_string(k++);
			cout << "Введите длительность и кол-во ядер для задачи " << name << ": ";
			cin >> time >> req;
			Task a(time, req, name);
			b.push_back(a);
		}
		cl.addTasks(b);
		cl.nextClock();
		cl.printStatistics(flag);
	}
}


int random(int a, int b, int l)
{
	srand(time(NULL) + 1000000 * l);
	return a + rand() % (b - a);
}


int main()
{
	setlocale(LC_ALL, "Russian");
	int minProcNumber, maxProcNumber, minCoresNumber, maxCoresNumber, minTasksPerClock, maxTasksPerClock, nClock, 
		minTimePerTask, maxTimePerTask, minCoresPerTask, maxCoresPerTask;
	cout << "Введите диапозон значений количества процессоров на кластере (два числа через пробел): ";
	cin >> minProcNumber >> maxProcNumber;
	cout << "Введите диапозон значений количества ядер в процессоре (два числа через пробел): ";
	cin >> minCoresNumber >> maxCoresNumber;
	cout << "Введите диапозон количества задач на одном такте (два числа через пробел): ";
	cin >> minTasksPerClock >> maxTasksPerClock;
	cout << "Введите кол-во тактов: ";
	cin >> nClock;
	cout << "Введите диапозон количества тактов, необходимых для выполнения одной задачи (два числа через пробел): ";
	cin >> minTimePerTask >> maxTimePerTask;
	cout << "Введите диапозон количества ядер, необходимых для выполнения одной задачи (два числа через пробел): ";
	cin >> minCoresPerTask >> maxCoresPerTask;
	cout << "Выводить статистику по загрузке каждого процессора? Y/N ";
	char a;
	bool flag = false;
	cin >> a;
	if (a == 'Y' || a == 'y')
		flag = true;
	int k = 0, l = 0;
	int nProc = random(minProcNumber, maxProcNumber, l++);
	vector<int> proc(nProc);
	for (int i = 0; i < nProc; ++i)
		proc[i] = random(minCoresNumber, maxCoresNumber, l++);
	Cluster cl(proc);
	for (int i = 0; i < nClock; ++i)
	{
		int nTasks = random(minTasksPerClock, maxTasksPerClock, l++);
		vector<Task> tasks(nTasks);
		for (int j = 0; j < nTasks; ++j)
		{
			string name = "task" + to_string(k++);
			int t = random(minTimePerTask, maxTimePerTask, l++), r = random(minCoresPerTask, maxCoresPerTask, l++);
			Task tsk(t, r, name);
			tasks[j] = tsk;
		}
		cout << endl << "Сгенерированные задачи:" << endl;
		for (int j = 0; j < nTasks; ++j)
		{
			cout << "\t" << tasks[j].getTaskName() << ": clocks to run " << tasks[j].getTime() << ", required cores: " << tasks[j].getCores() << endl;
		}
		cl.addTasks(tasks);
		cl.nextClock();
		cl.printStatistics(flag);
		Sleep(1000);
	}
	cout << "Общая загрузка кластера по всем тактам: " << cl.stat() * 100 << "%";
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.


