
#include <iostream>
#include <cmath>

#include <vector>
#include <stack>
#include <map>

#include "./vector.hpp"
#include "stack/stack.hpp"
#include "map/map.hpp"

#ifndef NS
#define NS ft
#endif

template <typename T>
void print_namespace(ft::vector<T> const &vec)
{
	vec.empty();
	std::cout << "\nNAMESPACE : ft" << std::endl;
}

template <typename T>
void print_namespace(std::vector<T> const &vect)
{
	vect.empty();
	std::cout << "\nNAMESPACE : std" << std::endl;
}

template <typename T>
void print_vector(NS::vector<T> &vect, char const *label)
{
	std::cout << "\nvector Size: " << vect.size();
	std::cout << "\nvector [" << label << "] contains:";
	if (!vect.size())
		std::cout << "\tnothing";
	for (typename NS::vector<T>::iterator it = vect.begin(); it != vect.end(); ++it)
	{
		std::cout << "  [ " << *it << " ]";
	}
	std::cout << std::endl;
}

template <typename T>
void print_namespace(ft::stack<T> const &stk)
{
	if (stk.size())
		stk.empty();
	std::cout << "\nNAMESPACE : ft" << std::endl;
}

template <typename T>
void print_namespace(std::stack<T> const &stk)
{
	if (stk.size())
		stk.empty();
	std::cout << "\nNAMESPACE : std" << std::endl;
}

template <typename T>
void print_stack(NS::stack<T> &mystk, char const *label)
{
	NS::stack<T> stk = mystk;
	std::cout << "\nstack Size: " << stk.size();
	std::cout << "\nstack [" << label << "] contains:";
	if (stk.empty())
		std::cout << "\tnothing";
	for (; stk.size();)
	{
		std::cout << " \n [ " << stk.top() << " ]";
		stk.pop();
	}
	std::cout << std::endl;
}

template <typename T, typename U>
void print_namespace(ft::map<T, U> const &mp)
{
	mp.empty();
	std::cout << "\nNAMESPACE : ft" << std::endl;
}

template <typename T, typename U>
void print_namespace(std::map<T, U> const &mp)
{
	mp.empty();
	std::cout << "\nNAMESPACE : std" << std::endl;
}

template <typename T, typename U>
void print_map(NS::map<T, U> &mp, char const *label)
{
	std::cout << "\nmap Size: " << mp.size();
	std::cout << "\nmap [" << label << "] contains: ";
	if (!mp.size())
		std::cout << "nothing";
	else
		std::cout << "\n\n";
	for (typename NS::map<T, U>::iterator it = mp.begin(); it != mp.end(); ++it)
	{
		std::cout << "[" << it->first << "]"
				  << " = " << it->second << std::endl;
	}
	std::cout << std::endl;
}

// a predicate implemented as a function:
bool single_digit(const int &value) { return (value < 10); }

// a predicate implemented as a class:
struct is_odd
{
	bool operator()(const int &value) { return (value % 2) == 1; }
};

// a binary predicate implemented as a function:
bool same_integral_part(double first, double second)
{
	return (int(first) == int(second));
}

// a binary predicate implemented as a class:
struct is_near
{
	bool operator()(double first, double second)
	{
		return (fabs(first - second) < 5.0);
	}
};

// compare only integral part:
bool mycomparison(double first, double second)
{
	return (int(first) < int(second));
}

int main(void)
{
	// vector tests
	std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< vector tests >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n"
			  << std::endl;
	NS::vector<int> vectGolbal;
	print_namespace(vectGolbal);
	// front() and back()
	{
		std::cout << "\nfront() & back()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::vector<int> myvect;
		int arr[5] = {1, 2, 3, 4, 5};
		NS::vector<int> myvect2(arr, arr + 5);

		print_vector(myvect2, "myvect2");

		myvect.push_back(77);
		myvect.push_back(22);

		print_vector(myvect, "myvect");

		// now front equals 77, and back 22

		myvect.front() -= myvect.back();

		std::cout << "myvect.front() is now " << myvect.front() << '\n';
		std::cout << "=======================================" << std::endl;
	}

	// max_size()
	{
		std::cout << "\nmax_size()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::vector<size_t> myvect;

		myvect.push_back(77);
		myvect.push_back(22);

		std::cout << "myvect.max_size() is: " << myvect.max_size() << '\n';
		std::cout << "=======================================" << std::endl;
	}

	// capacity()
	{
		std::cout << "\ncapacity()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::vector<size_t> vec(50, 500);
		NS::vector<size_t> myvect(4, 100);
		std::cout << "myvect.capacity() is: " << myvect.capacity() << '\n';
		std::cout << "myvect.size() is: " << myvect.size() << '\n';

		myvect.push_back(200);
		std::cout << "myvect.capacity() is: " << myvect.capacity() << '\n';
		std::cout << "myvect.size() is: " << myvect.size() << '\n';
		myvect.insert(myvect.begin(), vec.begin(), vec.end());

		std::cout << "myvect.capacity() is: " << myvect.capacity() << '\n';
		std::cout << "myvect.size() is: " << myvect.size() << '\n';

		myvect.push_back(200);
		std::cout << "myvect.capacity() is: " << myvect.capacity() << '\n';
		std::cout << "myvect.size() is: " << myvect.size() << '\n';
		std::cout << "=======================================" << std::endl;
	}

	// assign()
	{
		std::cout << "\nassign()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::vector<int> first;
		NS::vector<int> second;

		first.assign(7, 100); // 7 ints with value 100

		second.assign(first.begin(), first.end()); // a copy of first
		print_vector(first, "first");
		print_vector(second, "second");

		NS::vector<int> vect(3);
		first.assign(vect.begin(), vect.end());
		print_vector(first, "first");

		std::cout << "Size of first: " << int(first.size()) << '\n';
		std::cout << "Size of second: " << int(second.size()) << '\n';

		std::cout << "=======================================" << std::endl;
	}

	// insert()
	{
		std::cout << "\ninsert()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::vector<int> myvect;
		NS::vector<int>::iterator ite;

		// set some initial values:
		for (int i = 1; i <= 5; ++i)
		{
			myvect.push_back(i);
		}
		ite = myvect.begin();
		++ite;

		myvect.insert(ite++, 10);
		print_vector(myvect, "myvect");


		ite = myvect.begin();
		ite += 2;
		myvect.insert(ite, 2, 20);
		print_vector(myvect, "myvect");

		NS::vector<int> mytmp(2, 30);
		print_vector(mytmp, "mytmp");

		ite = myvect.begin();
		myvect.insert(ite, mytmp.begin(), mytmp.end());

		print_vector(myvect, "myvect");
		std::cout << "=======================================" << std::endl;
	}

	// erase()
	{
		std::cout << "\nerase()" << std::endl;
		std::cout << "=======================================" << std::endl;

		NS::vector<int> myvect;
		NS::vector<int>::iterator it1, it2;
		// set some values:
		for (int i = 1; i < 10; ++i)
			myvect.push_back(i * 10);

		print_vector(myvect, "myvect");

		// 10 20 30 40 50 60 70 80 90
		it1 = it2 = myvect.begin(); // ^^
		for (size_t i = 0; i < 6; i++, it2++)
			;  // ^                 ^
		++it1; //    ^              ^
		--it2;
		it1 = myvect.erase(it1); // 10 30 40 50 60 70 80 90
								 //    ^              ^

		print_vector(myvect, "myvect");
		std::cout << "*it1 = " << *it1 << std::endl;
		std::cout << "*it1 = " << *it2 << std::endl;

		it2 = myvect.erase(it2); // 10 30 40 50 60 80 90
								 //    ^           ^
		print_vector(myvect, "myvect");
		std::cout << "*it1 = " << *it1 << std::endl;
		std::cout << "*it1 = " << *it2 << std::endl;
		// 10 30 40 50 60 80 90
		++it1; //    ^           ^
		--it2; //       ^     ^
		std::cout << "*it1 = " << *it1 << std::endl;
		std::cout << "*it1 = " << *it2 << std::endl;
		// it1 = myvect.begin();
		it2 = myvect.end();
		myvect.erase(it1, it2); // 10 30 60 80 90
								//        ^

		print_vector(myvect, "myvect");

		std::cout << "=======================================" << std::endl;
	}

	// swap()
	{
		std::cout << "\nswap()" << std::endl;
		std::cout << "=======================================" << std::endl;
		// ft::vector
		NS::vector<int> first(3, 100);	// three ints with a value of 100
		NS::vector<int> second(5, 200); // five ints with a value of 200

		print_vector(first, "first");
		print_vector(second, "second");

		first.swap(second);

		print_vector(first, "first");
		print_vector(second, "second");

		std::cout << "=======================================" << std::endl;
	}

	// resize()
	{
		std::cout << "\nresize()" << std::endl;
		std::cout << "=======================================" << std::endl;

		NS::vector<int> myvect;

		// set some initial content:
		for (int i = 1; i < 10; ++i)
			myvect.push_back(i);

		print_vector(myvect, "myvect");
		myvect.resize(5);
		print_vector(myvect, "myvect");
        std::cout << "zabi\n" ;
		myvect.resize(8, 100);
		print_vector(myvect, "myvect");
		myvect.resize(12);
		print_vector(myvect, "myvect");

		std::cout << "=======================================" << std::endl;
	}

	// relational operators()
	{
		std::cout << "\nrelational operators" << std::endl;
		std::cout << "=======================================" << std::endl;

		NS::vector<int> a;
		a.push_back(10);
		a.push_back(20);
		a.push_back(30);
		print_vector(a, "a");
		NS::vector<int> b = a;
		// b = a;
		print_vector(b, "b");

		NS::vector<int> c;
		c.push_back(30);
		c.push_back(20);
		c.push_back(10);
		print_vector(c, "c");

		if (a == b)
			std::cout << "\na and b are equal\n";
		if (b != c)
			std::cout << "b and c are not equal\n";
		if (b < c)
			std::cout << "b is less than c\n";
		if (c > b)
			std::cout << "c is greater than b\n";
		if (a <= b)
			std::cout << "a is less than or equal to b\n";
		if (a >= b)
			std::cout << "a is greater than or equal to b\n";
		std::cout << "=======================================" << std::endl;
	}

	// non-member swap()
	{
		std::cout << "\nnon-member swap()" << std::endl;
		std::cout << "=======================================" << std::endl;

		NS::vector<int> foo(3, 100); // three ints with a value of 100
		NS::vector<int> bar(5, 200); // five ints with a value of 200

		print_vector(foo, "foo");
		print_vector(bar, "bar");
		NS::swap(foo, bar);
		print_vector(foo, "foo");
		print_vector(bar, "bar");

		std::cout << "=======================================" << std::endl;
	}

	// reverse iterators
	{
		std::cout << "\nreverse iterators" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::vector<int> l;
		l.push_back(1);
		l.insert(l.end(), 4, 100);
		l.push_back(2);
		NS::vector<int>::reverse_iterator ite = l.rbegin();
		NS::vector<int>::reverse_iterator it = l.rend();
		for (int i = 0; it != ite; ite++, i++)
		{
			std::cout << "[" << *ite << "]  ";
		}
		std::cout << "\n=======================================" << std::endl;
	}
	// const_iterator
	{
		std::cout << "\nconst iterators" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::vector<int> l;
		l.push_back(1);
		l.push_back(2);
		l.push_back(3);
		l.push_back(4);
		l.push_back(5);
		NS::vector<int>::const_iterator ite = l.begin();
		NS::vector<int>::const_iterator it = l.end();
		for (; it != ite; ite++)
		{
			std::cout << "[" << *ite << "]  ";
		}
		std::cout << "\n=======================================" << std::endl;
	}

	// iterator relational operators
	{
		std::cout << "\nrelational operators for iterator" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::vector<int> l;
		l.push_back(1);
		l.push_back(2);
		l.push_back(3);
		l.push_back(4);
		l.push_back(5);
		NS::vector<int>::const_iterator ite = l.begin();
		NS::vector<int>::const_iterator it = l.begin() + 2;
		std::cout << "first=" << *ite << std::endl;
		std::cout << "third=" << *it << std::endl;
		std::cout << "difference=" << it - ite << std::endl;

		std::cout << "\n=======================================" << std::endl;
	}
	std::cout << "\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< end of vector tests >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n"
			  << std::endl;
	//end of vector tests

	// stack tests
	std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< stack tests >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n"
			  << std::endl;
	NS::stack<int> stackGolbal;
	print_namespace(stackGolbal);
	// top() and empty()
	{
		std::cout << "\nfront() & back()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::stack<int> mystack;

		if (mystack.empty())
			std::cout << "mystack is empty" << std::endl;

		mystack.push(22);
		mystack.push(77);

		print_stack(mystack, "mystack");

		// now top equals 77
		std::cout << "mystack.top() is now " << mystack.top() << '\n';
		std::cout << "=======================================" << std::endl;
	}

	// size()
	{
		std::cout << "\nmax_size()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::stack<size_t> mystack;

		mystack.push(77);
		mystack.push(65);
		mystack.push(69);
		mystack.push(65);
		mystack.push(78);
		mystack.push(22);

		print_stack(mystack, "mystack");

		std::cout << "mystack.size() is: " << mystack.size() << '\n';
		std::cout << "=======================================" << std::endl;
	}

	// relational operators()
	{
		std::cout << "\nrelational operators" << std::endl;
		std::cout << "=======================================" << std::endl;

		NS::stack<int> a;
		a.push(10);
		a.push(20);
		a.push(30);
		print_stack(a, "a");
		NS::stack<int> b = a;
		// b = a;

		print_stack(b, "b");

		NS::stack<int> c;
		c.push(30);
		c.push(20);
		c.push(10);
		print_stack(c, "c");

		if (a == b)
			std::cout << "\na and b are equal\n";
		if (b != c)
			std::cout << "b and c are not equal\n";
		if (b < c)
			std::cout << "b is less than c\n";
		if (c > b)
			std::cout << "c is greater than b\n";
		if (a <= b)
			std::cout << "a is less than or equal to b\n";
		if (a >= b)
			std::cout << "a is greater than or equal to b\n";
		std::cout << "=======================================" << std::endl;
	}
	std::cout << "\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< end of stack tests >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n"
			  << std::endl;
	// end of stack tests

	// map tests
	std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< map tests >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n"
			  << std::endl;
	NS::map<int, int> maptGolbal;
	print_namespace(maptGolbal);

	// begin()
	{
		std::cout << "\nbegin() & end() " << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::map<int, int> map1;
		map1.insert(NS::make_pair(5, 1));
		map1.insert(NS::make_pair(10, 3));
		map1.insert(NS::make_pair(4, 4));
		map1.insert(NS::make_pair(2, 2));
		NS::map<int, int>::iterator it = map1.begin();
		print_map(map1, "map1");
		std::cout << "map1.begin(): " << (*it).first << std::endl;
		std::cout << "=======================================" << std::endl;
	}
	// assign operator=()
	{
		std::cout << "\nassign operator=()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::map<int, int> map1;
		map1.insert(NS::make_pair(5, 1));
		map1.insert(NS::make_pair(2, 2));
		map1.insert(NS::make_pair(10, 3));
		map1.insert(NS::make_pair(4, 4));
		print_map(map1, "map1");
		NS::map<int, int> map2;
		std::cout << "before assigning map1 to map2" << std::endl;
		print_map(map2, "map2");
		map2 = map1;
		std::cout << "after assigning map1 to map2" << std::endl;
		print_map(map2, "map2");
		std::cout << "=======================================" << std::endl;
	}

	// clear()
	{
		std::cout << "\nclear()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::map<int, int> map1;
		map1.insert(NS::make_pair(5, 1));
		map1.insert(NS::make_pair(2, 2));
		map1.insert(NS::make_pair(10, 3));
		map1.insert(NS::make_pair(4, 4));
		print_map(map1, "map1");
		map1.clear();
		std::cout << "after clearing map1" << std::endl;
		print_map(map1, "map1");
		std::cout << "=======================================" << std::endl;
	}

	// count()
	{
		std::cout << "\ncount()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::map<int, int> map1;
		map1.insert(NS::make_pair(5, 1));
		map1.insert(NS::make_pair(2, 2));
		map1.insert(NS::make_pair(10, 3));
		map1.insert(NS::make_pair(4, 4));
		print_map(map1, "map1");
		std::cout << "map1.count(5): " << map1.count(5) << std::endl;
		std::cout << "map1.count(6): " << map1.count(6) << std::endl;
		std::cout << "=======================================" << std::endl;
	}

	// empty() and size()
	{
		std::cout << "\nempty()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::map<int, int> map1;
		map1.insert(NS::make_pair(5, 1));
		map1.insert(NS::make_pair(2, 2));
		map1.insert(NS::make_pair(10, 3));
		map1.insert(NS::make_pair(4, 4));
		print_map(map1, "map1");
		std::cout << "map1.empty(): " << map1.empty() << std::endl;
		map1.clear();
		std::cout << "after clearing map1" << std::endl;
		print_map(map1, "map1");
		std::cout << "map1.empty(): " << map1.empty() << std::endl;
		std::cout << "=======================================" << std::endl;
	}

	// find()
	{
		std::cout << "\nfind()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::map<int, int> map1;
		map1.insert(NS::make_pair(5, 1));
		map1.insert(NS::make_pair(2, 2));
		map1.insert(NS::make_pair(10, 3));
		print_map(map1, "map1");
		if (map1.find(5) != map1.end())
			std::cout << "5 has been found and its second is = " << map1.find(5)->second << std::endl;
		else
			std::cout << "5 has not been found" << std::endl;
		if (map1.find(6) != map1.end())
			std::cout << "6 has been found and its second is = " << map1.find(6)->second << std::endl;
		else
			std::cout << "6 has not been found" << std::endl;
		std::cout << "=======================================" << std::endl;
	}

	// insert()
	{
		std::cout << "\ninsert()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::map<int, int> map1;
		map1.insert(NS::make_pair(5, 1));
		map1.insert(NS::make_pair(2, 2));
		map1.insert(NS::make_pair(10, 3));
		print_map(map1, "map1");
		NS::map<int, int>::iterator it = map1.insert(NS::make_pair(4, 4)).first;
		print_map(map1, "map1");
		std::cout << "inserted 4, 4 at " << (*it).first << std::endl;
		NS::pair<int, int> arr[] = {NS::make_pair(0, 20), NS::make_pair(2, 30),
									NS::make_pair(3, 40), NS::make_pair(4, 50)};
		NS::map<int, int> map2;
		map2.insert(arr, arr + 4);
		print_map(map2, "map2");
		std::cout << "=======================================" << std::endl;
	}

	// map constructors
	{
		std::cout << "\nmap constructors" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::map<int, int> map1;
		map1.insert(NS::make_pair(5, 1));
		map1.insert(NS::make_pair(2, 2));
		map1[10] = 3;
		map1[4] = 4;
		print_map(map1, "map1");
		NS::map<int, int> map2(map1);
		print_map(map2, "map2");
		NS::map<int, int> map3(map2.begin(), map2.end());
		print_map(map3, "map3");
		std::cout << "=======================================" << std::endl;
	}

	// erase()
	{
		std::cout << "\nerase()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::map<int, int> map1;
		map1.insert(NS::make_pair(0, 1));
		map1.insert(NS::make_pair(2, 2));
		map1.insert(NS::make_pair(10, 3));
		map1.insert(NS::make_pair(4, 4));
		map1.insert(NS::make_pair(3, 300));
		map1.insert(NS::make_pair(3, 300));
		map1.insert(NS::make_pair(1, 110));
		map1.insert(NS::make_pair(0, 10));
		print_map(map1, "map1");
		std::cout << "map1.erase(0): " << map1.erase(0) << std::endl;
		NS::map<int, int>::iterator it = map1.begin();
		std::advance(it, 2);
		map1.erase(map1.begin(), it);
		print_map(map1, "map1");
		map1.erase(map1.begin());
		print_map(map1, "map1");

		std::cout << "=======================================" << std::endl;
	}

	// max_size()
	{
		std::cout << "\nmax_size()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::map<int, int> map1;
		std::cout << "map1.max_size(): " << map1.max_size() << std::endl;
		std::cout << "=======================================" << std::endl;
	}

	// swap()
	{
		std::cout << "\nswap()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::map<int, int> map1;
		map1.insert(NS::make_pair(5, 1));
		map1.insert(NS::make_pair(2, 2));
		map1.insert(NS::make_pair(10, 3));
		map1.insert(NS::make_pair(4, 4));
		print_map(map1, "map1");
		NS::map<int, int> map2;
		map2.insert(NS::make_pair(0, 1));
		map2.insert(NS::make_pair(2, 2));
		map2.insert(NS::make_pair(10, 3));
		map2.insert(NS::make_pair(4, 4));
		print_map(map2, "map2");
		map1.swap(map2);
		print_map(map1, "map1");
		print_map(map2, "map2");
		std::cout << "=======================================" << std::endl;
	}

	// lower_bound()
	{
		std::cout << "\nlower_bound()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::map<int, int> map1;
		map1.insert(NS::make_pair(5, 1));
		map1.insert(NS::make_pair(2, 2));
		map1.insert(NS::make_pair(10, 3));
		map1.insert(NS::make_pair(4, 4));
		print_map(map1, "map1");
		NS::map<int, int>::iterator it = map1.lower_bound(3);
		std::cout << "map1.lower_bound(3): " << (*it).first << std::endl;
		it = map1.lower_bound(5);
		std::cout << "map1.lower_bound(5): " << (*it).first << std::endl;
		it = map1.lower_bound(6);
		std::cout << "map1.lower_bound(6): " << (*it).first << std::endl;
		std::cout << "=======================================" << std::endl;
	}

	// upper_bound()
	{
		std::cout << "\nupper_bound()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::map<int, int> map1;
		map1.insert(NS::make_pair(5, 1));
		map1.insert(NS::make_pair(2, 2));
		map1.insert(NS::make_pair(10, 3));
		map1.insert(NS::make_pair(4, 4));
		print_map(map1, "map1");
		NS::map<int, int>::iterator it = map1.upper_bound(3);
		std::cout << "map1.upper_bound(3): " << (*it).first << std::endl;
		it = map1.upper_bound(5);
		std::cout << "map1.upper_bound(5): " << (*it).first << std::endl;
		it = map1.upper_bound(6);
		std::cout << "map1.upper_bound(6): " << (*it).first << std::endl;
		std::cout << "=======================================" << std::endl;
	}

	// equal_range()
	{
		std::cout << "\nequal_range()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::map<int, int> map1;
		map1.insert(NS::make_pair(5, 1));
		map1.insert(NS::make_pair(2, 2));
		map1.insert(NS::make_pair(10, 3));
		map1.insert(NS::make_pair(4, 4));
		print_map(map1, "map1");
		NS::pair<NS::map<int, int>::iterator, NS::map<int, int>::iterator> range = map1.equal_range(3);
		std::cout << "map1.equal_range(3): " << (*range.first).first << " " << (*range.second).first << std::endl;
		range = map1.equal_range(5);
		std::cout << "map1.equal_range(5): " << (*range.first).first << " " << (*range.second).first << std::endl;
		range = map1.equal_range(6);
		std::cout << "map1.equal_range(6): " << (*range.first).first << " " << (*range.second).first << std::endl;
		std::cout << "=======================================" << std::endl;
	}

	// get_allocator()
	{
		std::cout << "\nget_allocator()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::map<int, int> map1;
		print_map(map1, "map1");
		NS::map<int, int>::allocator_type alloc = map1.get_allocator();
		NS::pair<const int, int> *ptr = alloc.allocate(1);
		alloc.deallocate(ptr, 1);
		std::cout << "alloc max size: " << alloc.max_size() << std::endl;

		std::cout << "=======================================" << std::endl;
	}

	// const iterators
	{
		std::cout << "\nconst iterators" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::map<int, int> map1;
		map1.insert(NS::make_pair(5, 1));
		map1.insert(NS::make_pair(2, 2));
		map1.insert(NS::make_pair(10, 3));
		map1.insert(NS::make_pair(4, 4));
		print_map(map1, "map1");
		NS::map<int, int>::const_iterator it = map1.begin();
		std::cout << "map1.begin(): " << (*it).first << std::endl;
		it = map1.end();
		--it;
		std::cout << "map1.end(): " << (*it).first << std::endl;
		std::cout << "=======================================" << std::endl;
	}

	// reverse iterators
	{
		std::cout << "\nreverse iterators" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::map<int, int> map1;
		map1.insert(NS::make_pair(5, 1));
		map1.insert(NS::make_pair(2, 2));
		map1.insert(NS::make_pair(10, 3));
		map1.insert(NS::make_pair(4, 4));
		print_map(map1, "map1");
		NS::map<int, int>::reverse_iterator it = map1.rbegin();
		// print all elements in reverse order
		for (; it != map1.rend(); ++it)
		{
			std::cout << "[" << (*it).first << "] = " << (*it).second << std::endl;
		}

		std::cout << "=======================================" << std::endl;
	}

	std::cout << "\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< end of map tests >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n"
			  << std::endl;
	// end of map tests

	std::cout << "end of program" << std::endl;
	return 0;
}
