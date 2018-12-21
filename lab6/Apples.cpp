// sorting apples
// non STL-algorithm code to be replaced by algorthms
// Mikhail Nesterenko
// 2/16/2018

// get first half from other computer
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <functional>
#include <algorithm>
#include <numeric>
#include <iterator>

using std::cin; 
using std::cout; 
using std::endl;
using std::string;
using std::vector; 
using std::deque;
using namespace std::placeholders;


struct Apple {
	double weight; // oz
	string color;  // red or green
	void print() const { cout << color << ", " << weight << endl; }

	bool operator<(const Apple& rhs) const {
		return this->weight < rhs.weight;
	}
	void print(int appleNumber) {
		cout << "Apple " << appleNumber++ << ": Weight=" << weight << ",  Color = " << color << "\n";
	}

	// used for transform
	void operator=(double newWeight) {
		this->weight = newWeight;
	}
};

// used this function to practice bind functions later
bool greaterWeight(Apple a, double toFind) { 
	return a.weight > toFind;
}

// used this class to practice bind functor later
class greaterFunctor {
public:
	greaterFunctor(double toFind) : callCount(0), toFind_(toFind) {}
	bool operator() (Apple a) { 
		if (a.weight > toFind_) { 
			cout << callCount++ << ", "; 
			return true; 
		}
		++callCount;
		return false;
	}
private:
	int callCount;
	double toFind_;
};

int main() {
	srand(static_cast<unsigned int>(time(nullptr)));
	const double kMinWeight = 8.;
	const double kMaxWeight = 3.;

	cout << "Input crate size: ";
	int size;
	cin >> size;

	vector <Apple> crate(size);

	// assign random weight and color to apples in the crate
	generate(crate.begin(), crate.end(), [=]() { Apple a; 
		a.weight = kMinWeight + static_cast<double>(rand()) / RAND_MAX*(kMaxWeight - kMinWeight);
		a.color = rand() % 2 == 1 ? "green" : "red"; 
		return a;});

	cout << "Enter weight to find: ";
	double toFind;
	cin >> toFind;
	

	cout << "There are " << 
		count_if(crate.begin(), crate.end(), bind(greaterWeight, _1, toFind))
		<< " apples heavier than "
		<< toFind << " oz" << endl;

	// i used for each because it is a good solution to the problem we discussed in class
	// I hope this is acceptable because find_if() shouldn't be used here
	// i used a functor here 
	greaterFunctor gf(toFind);
	cout << "at positions ";
	for_each(crate.begin(), crate.end(), gf);
	cout << endl;

	// max_element()
	auto heaviest = max_element(crate.begin(), crate.end());
	cout << "Heaviest apple weighs: " << heaviest->weight << " oz" << endl;
	
	// for_each() or accumulate()
	double sum = accumulate(crate.begin(), crate.end(), 0, [=] (double sum, Apple a) {return sum + a.weight; });
	cout << "Total apple weight is: " << sum << " oz" << endl;


	// transform();
	cout << "How much should they grow: ";
	double toGrow;
	cin >> toGrow;
	transform(crate.begin(), crate.end(),
		crate.begin(), 
		[=](Apple a) {return a.weight += toGrow;});
	
	// remove_if()
	cout << "Input minimum acceptable weight: ";
	double minAccept;
	cin >> minAccept;
	auto removed = remove_if(crate.begin(), crate.end(), 
		[=](Apple a) -> bool {return (a.weight < minAccept); });
	crate.erase(removed, crate.end());
	cout << "removed " << size - crate.size() << " elements" << endl;

	// bubble sort, replace with sort()
	sort(crate.begin(), crate.end());


	// moving all red apples from crate to peck
	vector<Apple> peck; // changed this to vector
	// stack overflow says remove_copy_if() dosen't remove  and it can't be done. 
	remove_copy_if(crate.begin(), crate.end(), back_inserter(peck),
		[](Apple a) {return a.color != "red";});

	removed = remove_if(crate.begin(), crate.end(), [](Apple a) {return (a.color == "red"); });
	crate.erase(removed, crate.end());

	// for_each() possibly
	int counter = 1;
	cout << "Apples in the crate:\n" << endl;
	for_each(crate.begin(), crate.end(), [&](Apple a) {a.print(counter++); });
	cout << endl;

	counter = 1;
	cout << "Apples in the peck:\n" << endl;
	for_each(peck.begin(), peck.end(), [&](Apple a) {a.print(counter++); });
}
