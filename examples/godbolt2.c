// -std=c17 -O1 -Wall -Wextra -pedantic -Wno-unused-variable

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

// accepts anything
void print_o(int* num){
    printf("%d\n", *num);
}

// at least one valid item (non-null) 
void print_m(int num[static 1]){
    printf("%d\n", *num);
}

// at least 5 valid items
void print5_m(int num[static 5]){
    printf("%d\n", num[0]);
    printf("%d\n", num[4]);
}


int main(void){
    int to_small[] = {1, 2, 3};
    int *pto_small = to_small;

    int *dto_small = malloc(sizeof(int[3]));
    memcpy(dto_small, to_small, sizeof(to_small));

    print_m(NULL);

    // int* invalid = NULL;
    // print_m(invalid);


    // print5_m(to_small);
    // print5_m(pto_small);
    // print5_m(dto_small);

}