#include <iostream>

using namespace std;

// Since chapter 22 is about designing class hierarchies, we will see how to implement a mixin here
// Based on http://www.thinkbottomup.com.au/site/blog/C%20%20_Mixins_-_Reuse_through_inheritance_is_good

struct MyTask
{
	void execute() { cout << "--- MyTask executes! ---" << endl; }
};

template <typename T>
struct TimingMixin : public T
{
	void execute()
	{
		cout << "TIMER start!" << endl;
		T::execute();
		cout << "TIMER stop!" << endl;
	}
};

template <typename T>
struct LoggingMixin : public T
{
	void execute()
	{
		cout << "LOG: execution ENTER" << endl;
		T::execute();
		cout << "LOG: execution EXIT" << endl;
	}
};


int main()
{
	TimingMixin<MyTask> timedTask;
	timedTask.execute();

	cout << endl;

	LoggingMixin<MyTask> loggedTask;
	loggedTask.execute();

	cout << endl;

	LoggingMixin<TimingMixin<MyTask>> loggedTimedTask;
	loggedTimedTask.execute();
}
