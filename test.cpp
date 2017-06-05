//g++ -shared -o libhello.so -fPIC test.cpp

#include <iostream>

extern "C" void hello(){
	std::cout << "hello world!Fine" << std::endl;
}

