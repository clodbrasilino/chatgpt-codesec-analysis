#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool is_even(int number);

bool is_even(int number) {
    return (number % 2 == 0);
}

int main(void) {
    int test_number = 42;
    
    if (is_even(test_number)) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    
    return EXIT_SUCCESS;
}