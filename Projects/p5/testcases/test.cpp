#include <iostream>
#include "dlist.h"
#include <cassert>

using namespace std;

int main()
{
	Dlist<int> ilist;

	// Test isEmpty on empty list
	assert(ilist.isEmpty());

	// Test insertFront
	int *ip1 = new int(1);
	ilist.insertFront(ip1);
	assert(!ilist.isEmpty());

	// Test insertBack
	int *ip2 = new int(2);
	ilist.insertBack(ip2);

	// Test removeFront
	int *ip = ilist.removeFront();
	assert(*ip == 1);
	delete ip;

	// Test removeBack
	ip = ilist.removeBack();
	assert(*ip == 2);
	delete ip;

	// Test isEmpty after removals
	assert(ilist.isEmpty());

	// Test removeFront on empty list (should throw exception)
	try
	{
		ilist.removeFront();
		assert(false); // Should not reach here
	}
	catch (emptyList &)
	{
		std::cout << "emptyList exception caught" << std::endl;
		// Expected exception
	}

	// Test removeBack on empty list (should throw exception)
	try
	{
		ilist.removeBack();
		assert(false); // Should not reach here
	}
	catch (emptyList &)
	{
		std::cout << "emptyList exception caught" << std::endl;
		// Expected exception
	}

	// Test copy constructor
	int *ip3 = new int(3);
	int *ip4 = new int(4);
	ilist.insertFront(ip3);
	ilist.insertBack(ip4);
	Dlist<int> ilistCopy(ilist);

	ip = ilistCopy.removeFront();
	assert(*ip == 3);
	delete ip;

	ip = ilistCopy.removeBack();
	assert(*ip == 4);
	delete ip;

	// Test assignment operator
	Dlist<int> ilistAssign;
	int *ip5 = new int(5);
	ilistAssign.insertFront(ip5);
	ilistAssign = ilist;

	ip = ilistAssign.removeFront();
	assert(*ip == 3);
	delete ip;

	ip = ilistAssign.removeBack();
	assert(*ip == 4);
	delete ip;

	// Test self-assignment
	ilistAssign = ilistAssign;

	cout << "All tests passed!" << endl;
	return 0;
}