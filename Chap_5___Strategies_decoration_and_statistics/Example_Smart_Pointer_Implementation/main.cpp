#include <iostream>
#include <memory> // for std::move
#include "My_UniquePtr.h"
#include "Resource.h"

int main() {

	/*
	// USING My_UniquePtr.h

	My_UniquePtr<Resource> p1{ new Resource };
	My_UniquePtr<Resource> p2;

	std::cout << "p1 is managing Resource? " << p1.isAssigned() << "\n";
	std::cout << "p2 is managing Resource? " << p2.isAssigned() << "\n";

	std::cout << "Resource exchange...\n";
	p2 = std::move(p1);

	std::cout << "p1 is managing Resource? " << p1.isAssigned() << "\n";
	std::cout << "p2 is managing Resource? " << p2.isAssigned() << "\n";

	*/

	// USING My_UniquePtr.h

	return 0;
}
