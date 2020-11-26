#ifndef RESOURCE
#define RESOURCE

#include <iostream>

class Resource {

public:

	Resource()
	{
		std::cout << "Resource acquired\n";
	}

	~Resource()
	{
		std::cout << "Resource destroyed.\n";
	}
};
#endif
