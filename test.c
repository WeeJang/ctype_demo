//g++ -shared -o libhello.so -fPIC test.cpp


#include <stdio.h>

void hello(void);

void hello(){
    printf("hello world!\n");
}

