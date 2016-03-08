#include <iostream>
#include <stdlib.h>
#include <exception>
#include <csignal>
using namespace std;

/*
exception safety provided by std lib:
-basic guarantee - no resource leaks, object can be destroyed/assigned to
-strong guarantee - either the operation succeeds or the object remains in intact state
-nothrow guarantee - no exceptions are thrown by this operation
*/





// noexcept example. This helps compilator to optimize the code better and tells people this func dont know how to deal with exceptions
void cantThrowExceptions() noexcept // it used to be throw() in '98. or throw(int) to say the func can only throw int exceptions. obsolete
{
	// if this function threw exception anyway, the terminate() function would be called immidiately and no cleanup would be done
	cout << "This func is noexcept" << endl;
}

// callIt declares noexcept only if "f" declares noexcept. This must be known compiletime
template <typename F>
void callIt(F f) noexcept(noexcept(f())) 
{
	f();
}

void noexceptExample()
{
	try {
		callIt(cantThrowExceptions);
	} catch (...) {}
}


// Finally trick example
template <typename F>
struct Finally
{
	F cleanFunc;
	Finally(F cleanFunc) : cleanFunc {cleanFunc} {}
	~Finally() { cleanFunc(); }
};

template <typename F>
Finally<F> finally(F func) 
{
	return Finally<F>(func);
}

void dangerousOperation()
{
	// !!! beware: the automatic object destructor is only called, if the exception is try-catched somewhere!!!
	int *p = new int[25];

	// create finalize object that frees the memory
	auto onExit = finally([&] { delete[] p; p = nullptr; cout << "auto cleanup even if exception thrown" << endl; });

	throw 1; // onExit is called due to stack unwinding

	// never happens
	delete[] p;
}

void finallyExample()
{
	try {
		dangerousOperation();
	}
	catch (...) {
	}
}


// Program exit methods example.  exit, quick_exit, abort, terminate
[[noreturn]] void abortHandler(int sigNo)
{
	// sigNo == 6 for SIGABRT
	cout << "abort() called, signal sent, handler in action, signalNo=" << sigNo << endl;

	// The function is a noreturn, the program must exit. Unless we use trick and jmp to some other location :)
	// _Exit == quick_exit, but doesnt call any registered atexit/at_quick_exit functions
	_Exit(1);
}

[[noreturn]] void terminateHandler()
{
	cout << "terminate() called, handler in action" << endl;

	// The function is a noreturn, the program must exit.  Unless we use trick and jmp to some other location :)
	_Exit(1);
}

void programExitMethodsExample()
{
	// makes cleanup of thread local storage, static storage, IO streams
	// calls functions registerd with atexit() and returns control to host env
	exit(0);

	// calls functions registered with at_quick_exit() and returns control to host env
	// no cleanup phase, but IO streams cleanup depends on implementation
	quick_exit(0);


	// calls the current terminate handler, setup with set_terminate(). By default it is set to abort
	// used for uncought exceptions
	set_terminate(terminateHandler);
	terminate();	

	// calls raise(SIGABRT) that can be handled by handler formerly pointed by signal(SIGABRT, handlerFunc)
	// if SIGABRT not handled, the application terminates with abnormal code
	// no cleanup is done, no functions registered with atexit nor at_quick_exit are called
	signal(SIGABRT, abortHandler);
	abort(); 
}	


int main()
{
	try {
		noexceptExample();
		finallyExample();
		programExitMethodsExample();
	} catch (exception &err) {
		// catch entire hierarchy of exceptions where "exception" is the root
	} catch (...) {
		// last exception can be retrieved as "exception_ptr" from current_exception() and passed eg. from worker thread to main thread
		// promise.set_exception(current_exception());
	}
}
