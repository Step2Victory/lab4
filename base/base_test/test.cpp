#include "pch.h"
#include "../Cluster/Cluster.h"


TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
}

TEST(Queue, Test1)
{
	Queue<int> a;
	EXPECT_TRUE(a.isEmpty());
}

TEST(Queue, Test2)
{
	Queue<int> a;
	a.push(1);
	EXPECT_FALSE(a.isEmpty());
}

TEST(Queue, Test3)
{
	Queue<int> a;
	a.push(1);
	EXPECT_EQ(a.pop(), 1);
}

TEST(Queue, Test4)
{
	Queue<int> a;
	ASSERT_ANY_THROW(a.pop());
}

TEST(Queue, Test5)
{
	Queue<int> a;
	a.push(1);
	a.pop();
	ASSERT_ANY_THROW(a.pop());
}

TEST(Queue, Test6)
{
	Queue<int> a;
	a.push(1);
	a.push(10);
	EXPECT_EQ(a.pop(), 1);
}

TEST(Queue, Test7)
{
	Queue<int> a;
	ASSERT_ANY_THROW(a.top());
}

TEST(Queue, Test8)
{
	Queue<int> a;
	a.push(1);
	a.push(10);
	EXPECT_EQ(a.top(), 1);
}



TEST(Task, Test1)
{
	Task a;
	EXPECT_TRUE(a.isReady());
}

TEST(Task, Test2)
{
	Task a(5);
	EXPECT_FALSE(a.isReady());
}

TEST(Task, Test3)
{
	ASSERT_ANY_THROW(Task a(-1));
}

TEST(Task, Test4)
{
	Task a(1);
	a--;
	EXPECT_TRUE(a.isReady());
}

TEST(Task, Test5)
{
	Task a(0);
	ASSERT_ANY_THROW(a--);
}

TEST(Task, Test6)
{
	Task a(10);
	for (int i = 0; i < 10; ++i)
		a--;
	EXPECT_TRUE(a.isReady());
}

TEST(Task, Test7)
{
	ASSERT_ANY_THROW(Task a(1, 0));
}

TEST(Task, Test8)
{
	Task a(1, 5);
	EXPECT_EQ(5, a.getCores());
}

TEST(Task, Test9)
{
	Task a(2, 3, "Task");
	EXPECT_EQ(2, a.getTime());
}

TEST(Task, Test10)
{
	Task a(2, 3, "Task");
	EXPECT_EQ("Task", a.getTaskName());
}


TEST(Processor, Test1)
{
	Processor a(4);
	Task b(3,1);
	EXPECT_TRUE(a.addTask(b));
}

TEST(Processor, Test2)
{
	Processor a(4);
	Task b(3, 5);
	EXPECT_FALSE(a.addTask(b));
}

TEST(Processor, Test3)
{
	Processor a(4);
	EXPECT_EQ(a.cores(), 4);
}

TEST(Processor, Test4)
{
	Processor a(4);
	EXPECT_EQ(a.freeCores(), 4);
}

TEST(Processor, Test5)
{
	Processor a(4);
	Task b(2, 2);
	a.addTask(b);
	EXPECT_EQ(a.freeCores(), 2);
}

TEST(Processor, Test6)
{
	Processor a(4);
	Task b(1, 4);
	a.addTask(b);
	a.nextClock();
	a.delReadyTasks();
	EXPECT_TRUE(a.isEmpty());
}

TEST(Processor, Test7)
{
	Processor a(4);
	Task b(1, 2);
	Task c(2, 2);
	a.addTask(b);
	a.addTask(c);
	a.nextClock();
	a.delReadyTasks();
	EXPECT_FALSE(a.isEmpty());
}

TEST(Processor, Test8)
{
	Processor a(4);
	Task b(1, 2);
	Task c(2, 2);
	a.addTask(b);
	a.addTask(c);
	a.nextClock();
	a.delReadyTasks();
	a.nextClock();
	a.delReadyTasks();
	EXPECT_TRUE(a.isEmpty());
}

TEST(Processor, Test9)
{
	Processor a(8);
	Task b(1, 2);
	Task c(2, 2);
	a.addTask(b);
	a.addTask(c);
	a.nextClock();
	a.delReadyTasks();
	EXPECT_EQ(a.freeCores(), 6);
}

TEST(Processor, Test10)
{
	Processor a(8);
	Task b(1, 2);
	Task c(2, 2);
	a.addTask(b);
	a.addTask(c);
	EXPECT_EQ(a.freeCores(), 4);
}

TEST(Cluster, Test1)
{
	ASSERT_ANY_THROW(Cluster a({ 1,2,-2,4 }));
}

TEST(Cluster, Test2)
{
	ASSERT_ANY_THROW(Cluster a({}));
}

