// -std=c17 -O2 -Wall -Wextra -pedantic -Wno-unused-variable

#include <stddef.h>

int sum(size_t n, int* arr){
    int ret = 0;
    for (size_t i = 0; i < n; ++i )
        ret += arr[i];
    
    return ret;
}

void init(size_t n, int *arr){
	for (size_t i = 0; i < n; ++i)
	    arr[i] = (i+1) * (i+1);
}
 

 int test_vla(size_t n){
	int arr[n];
	
	init(n, arr);
	return sum(n, arr);
}

	
int test_known_size(){
	int arr[10];
	
	init(10, arr);
	return sum(10, arr);
}

#define TEST_VLA (1)
 
int main(void){
    // the exit code 129 is linux 
    // turning the return value of 385 
    // into something else
    // check assembly for main: to see what really happens

	size_t n = 10;
	return TEST_VLA? 
	    test_vla(n) : 
	    test_known_size();
}
