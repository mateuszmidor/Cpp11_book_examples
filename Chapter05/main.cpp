#include <iostream>
#include <thread>
#include <mutex>
#include <memory>
#include <deque>
#include <chrono>
#include <condition_variable>
#include <future>
#include <functional> // std::ref
#include <ctime>
#include <type_traits>
#include <utility>
#include <numeric>
#include <random>
#include <valarray>
#include <limits>

using namespace std;

// Low level multithreading - thread, mutex, condition_variable
class BlockingQueue
{
private:
	// our two-ended container for storing elements
	deque<string> queue;

	// mutex to ensure exclusive access to the queue
	mutex m;

	// contidion variable to notify pending "get" that there is new element in the queue
	condition_variable elementAddedToQueue;
public:
	~BlockingQueue()
	{
		cout << "BlockingQueue destroyed" << endl;
	}

	string get()
	{
		unique_lock<mutex> lock {m};
		auto queueNotEmpty = [this]{ return !queue.empty(); };

		// wait until some element is added to the queue
		// now this is tricky;
		// the elementAddedToQueue releases lock and waits for "notify" call, but can also wake up on spontan
		// when it wakes up then it checks the queueNotEmpty predicate
		// if false - it waits again
		// if true - the lock is acquired and current thread is activated
		elementAddedToQueue.wait(lock, queueNotEmpty);
	 	
		string element = queue.front();
		queue.pop_front();
		return element;
	}

	void put(const string &element)
	{
		unique_lock<mutex> lock {m};
		queue.push_back(element);
		elementAddedToQueue.notify_one();
	}	
};


const string DONE_SENTINEL { "DONE" };

void producer(shared_ptr<BlockingQueue> q)
{
	string INVOC[] {"Litwo, ", "ojczyzno", "moja", "ty", "jestes", "jak", "zdrowie"};
	for (string s : INVOC)
	{
		q->put(s);
		this_thread::sleep_for(chrono::seconds(1));
	}
	q->put(DONE_SENTINEL);
}

void consumer(string consumerName, shared_ptr<BlockingQueue> q)
{
	while (true)
	{
		string s = q->get();
		if (s == DONE_SENTINEL) break;

		cout << consumerName << ": " << s << endl;
	}	
	q->put(DONE_SENTINEL);
}	

void producerConsumer()
{
	shared_ptr<BlockingQueue> queue { new BlockingQueue() };
	
	thread p1 { producer, queue };
	thread c1 { consumer, "Andrzej", queue };
	thread c2 { consumer, "Marian", queue };

	p1.join();
	c1.join();
	c2.join();

	// queue is destroyed by shared_ptr
}
 
// Async - future
void asyncFuture()
{
	auto heavyCalculationFunc = [] { return 1*2*3*4; };

	// run the asynchronous calculation.
	// actually the library decides if new thread should be spawned
	// or simply the calculation should be delegated until "get()" is called.
	// To ensure new thread - use async(std::launch::async, heavyCalculationFunc)
	// To ensure delegation - use async(std::launch::sync, heavyCalculationFunc)
	future<int> futureResult = async(heavyCalculationFunc);
 	cout << "Handling normal task like GUI, calculation ongoing in background..." << endl;	
	cout << "Heavy calculation result is " << futureResult.get() << endl;
}

// Promise - future
void promiseFuture()
{
	auto heavyCalculationFunc = [] (promise<int> &result) { result.set_value(4*3*2*1); };

	// promise allows to set the result value
	promise<int> promiseResult;

	// future allows to retrieve the result value
	future<int> futureResult = promiseResult.get_future();
	
	// run the function in new thread.
	// It promises to figureout and return the result :)
	// Notice the ref, it is needed as promise have no copy constructor 
	thread t { heavyCalculationFunc, ref(promiseResult) };		
 	cout << "Handling normal task like GUI, calculation ongoing in background..." << endl;	
	cout << "Heavy calculation result is " << futureResult.get() << endl;
	t.detach();
}

// Chrono
void chronoTime()
{
	using namespace chrono;
	const int NUM_STARS {1000};
	high_resolution_clock::time_point start = high_resolution_clock::now();
	for (int i = 0; i < NUM_STARS; i++)
		cout << '*';
	high_resolution_clock::time_point end = high_resolution_clock::now();
	
	cout << endl << NUM_STARS <<" stars printed in " << duration_cast<microseconds>(end-start).count() << "us" << endl;
}

// Type traits (tag dispatching)
struct printer_tag_normal {};
struct printer_tag_inbraces {}; 

template <typename T>
void print(T what)
{
	using printer = typename T::printer_tag;
	printHelper(what, printer{});
}

template<typename T>
void printHelper(T what, printer_tag_normal)
{
	cout << what.contents << endl;
}

template<typename T>
void printHelper(T what, printer_tag_inbraces)
{
	cout << "{ " << what.contents << " }" << endl;
} 

class NormalPrintable
{
public:
	using printer_tag = printer_tag_normal;
	const char* contents = "NormalPrintable";
};


class InBracesPrintable
{
public:
	using printer_tag = printer_tag_inbraces;
	const char* contents = "InBracesPrintable";
};

void typeTraits()
{
	print(NormalPrintable {});
	print(InBracesPrintable {});
}

// Type predicate
void typePredicate()
{
	cout << "Is float arithmetic? - " << is_arithmetic<float>::value << endl;
	cout << "Is string arithmetic? - " << is_arithmetic<string>::value << endl;

	// Note there is loads of other than is_arithmetic predicates in <type_traits>
}

// Pair 
void pairType()
{
	auto p = make_pair("Mateusz", 5.0);
	string name = p.first;
	double grade = p.second;
	cout << "pair extracted: first " << name << " second " << grade << endl;
}

// Tuple
void tupleType()
{
	auto t = make_tuple("Mateusz", "Biology", 5.0);
	string name = get<0>(t);
	string subject = get<1>(t);
	double grade = get<2>(t);
	// or just tie(name, subject, grade) = t;
	cout << "tuple extracted 0. " << name << " 1. " << subject << " 2. " << grade <<endl;
}

// cmath & numeric
void cmathNumeric()
{
	int n[] { 1, 2, 3, 4 };
	int sum = accumulate(begin(n), end(n), 0);
	cout << "Accumulate of 1,2,3,4 is " << sum << endl;
}

// Random num generators
void randomGenerator()
{
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	uniform_int_distribution<> one_to_six {1, 6}; 
	default_random_engine random_engine {seed};
	auto toss = bind(one_to_six, random_engine);

	cout << "Random numbers are: ";
	for (int i = 0; i < 6; i++)
		cout << toss() << " ";	
	cout << endl;
}

// Value arrays
void valueArray()
{
	// just do maths on vectors, like in any 3d math library
	valarray<double> v1 { 1, 2, 3};
	valarray<double> v2 { 2, 0, 0};
	auto v3 = (v1 + v2) / 2.0 + 1;
	cout << "([1, 2, 3] + [2, 0, 0]) / 2.0 + 1 = [" << v3[0] << ", " << v3[1] << ", " << v3[2] << "]" << endl;
}

// Numeric limits
template <typename T>
void printTypeLimits(const string typeName)
{
	const char TAB { '\t' };
	using  limits = numeric_limits<T>;
	cout << typeName << TAB << limits::lowest() << TAB << limits::max() << TAB << limits::is_signed<< endl;
}

void limits()
{
	cout << "type\tlowest\t\tmax\t\tis_signed" << endl;
	printTypeLimits<int>("int");
	printTypeLimits<float>("float");
	printTypeLimits<double>("double");
}

int main()
{
	producerConsumer();
	asyncFuture();
	promiseFuture();
	chronoTime();
	typeTraits();
	typePredicate();
	pairType();
	tupleType();
	cmathNumeric();
	randomGenerator();
	valueArray();
	limits();
}
