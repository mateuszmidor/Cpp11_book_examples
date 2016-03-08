#include <iostream>
#include <thread>
#include <future>
#include <condition_variable>
#include <chrono>
#include <exception>

using namespace std;
using namespace chrono;
// thread
void threadExample()
{
	cout << "thread::hardware_concurrency: " << thread::hardware_concurrency();	
	cout << endl << endl;
}

// detach
void printInLoop() 
{
	for (int i = 0; i < 10; ++i)
	{
		cout << "tick..." << flush; 
		this_thread::sleep_for(milliseconds(100)); 
	}
}

void detachExample()
{
	// local scope for thread to detach
	{
		thread t { printInLoop };
		t.detach();
	} // "t" object destroyed here, but the work is ongoing

	cout << "detach: thread object died but the detached system thread works on" << endl;
	this_thread::sleep_for(milliseconds(1000)); 

	cout << endl << endl;
}

// thread_local 
void threadlocalExample()
{
	cout << "thread_local:\n";
	thread_local unsigned n = 1;
	auto work = [&](char name) { n++; cout << "'n' for " << name << " = " << n << endl;; };
	thread a(work, 'a'), b(work, 'b');
	a.join();
	b.join();
	cout << "'n' for main = " << n;	

	cout << endl << endl;
}

// async, exception
int divide (int a, int b) 
{ 
	if (b == 0) throw invalid_argument("division by zero exception");
	return a / b;
}

void asyncExample()
{
	cout << "async divide(10, 5): ";
	cout << async(divide, 10, 5).get() << endl;

	// exceptions can be easily passed between threads
	cout << "async divide(10, 0): ";
	try {
		async(divide, 10, 0).get();
	}
	catch (const exception &e) {
		cout << e.what() << endl;
	}

	cout << endl;
}

// packaged_task, exception
void packedtaskExample()
{
	packaged_task<int(int, int)> doDivide(divide);
	
	cout << "packaged_task(divide, 20, 4): ";
	doDivide(20, 4);
	cout << doDivide.get_future().get() << endl;

	// exceptions can be easily passed
	doDivide.reset();
	cout << "packaged_task(divide, 20, 0): ";
	doDivide(20, 0);
	try {
		doDivide.get_future().get();
	}
	catch (const exception &e) {
		cout << e.what() << endl;
	}

	cout << endl;	
}

// condition_variable, also condition_variable_any to use with any lockable not only unique_lock
void conditionvariableExample()
{
	mutex m;
	condition_variable cv;
	bool jobDone = false;
	auto waitPrint = [&](string msg) 
	{ 
		cout << "condition_variable: start delay..." << endl;
		this_thread::sleep_for(seconds(1)); 
		cout << msg << endl; 
		unique_lock<mutex> lck(m); // "jobDone" is shared state; protect it
		jobDone = true;
		cv.notify_one();
	};

	thread t(waitPrint, "1 second delay print!");
	t.detach();

	unique_lock<mutex> lck(m); // lock_guard is simpler brother of unique_lock
	cv.wait(lck, [&jobDone]() { return jobDone; }); // lck.unlock() and wait for notify_one(). Then lck.lock() and proceed
	cout << "Printer thread jobDone!" << endl;

	cout << endl;
}

// call_once - good for initialization of global state
void print(string name)
{
	cout << "called from thread " << name << endl;
}

once_flag flag;
void doOnce(string name)
{
	call_once(flag, print, name);	
}

void callonceExample()
{
	cout << "call_once, threads t1 & t2: ";
	thread t1(doOnce, "t1");
	thread t2(doOnce, "t2");
	t1.join();
	t2.join();
}

// mutex, recursive_mutex, timed_mutex, recursive_timed_mutex
// lock(m1, m2, m3, ...), try_lock(m1, m2, m3,...) - lock all mutexes or none to avoid deadlocks

int main()
{
	threadExample();
	detachExample();
	threadlocalExample();
	asyncExample();
	packedtaskExample();
	conditionvariableExample();
	callonceExample();
}	
