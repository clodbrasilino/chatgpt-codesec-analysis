#include <stdio.h>
#include <stdbool.h>

bool is_even(int number) {
    return (number % 2) == 0;
}

int main(void) {
    int test_number = 42;
    
    if (is_even(test_number)) {
        printf("%d is even.\n", test_number);
    } else {
        printf("%d is odd.\n", test_number);
    }
    
    return 0;
}