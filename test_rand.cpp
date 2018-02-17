#include "rand.h"
#include <iostream>

#include <iostream>

int main() { 
	generator g(100);

	for (int i = 0; i < 100; i++) {
		std::cout << g() << "\t";
		if ((i+1) % 10 == 0)
			std::cout << "\n";
	}
	std::cout << "\n";
}
