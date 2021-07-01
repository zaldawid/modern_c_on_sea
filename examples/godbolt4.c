#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

// -std=c17 -O0 -Wall -Wextra -pedantic
// Play with the optimization level flag

typedef struct string{
    size_t sz_arr;
    size_t length;
    char *arr;
} string_s;
	
string_s mk_string(const char str[static 1]){
 
	size_t sz = strlen(str);
 
	string_s s = {
			.sz_arr = sz + 1,
			.length = sz,
			.arr = malloc(sz + 1)
		};
 
	if (s.arr){
		memcpy(s.arr, str, sz +1);
	}
	else{
		s = (string_s){0};
	}
	return s;
}

void func_val(string_s s){
	printf("%s", s.arr);
}

void call_by_val(void){
    string_s str = mk_string("Alice learns C!");
    func_val(str);
}

