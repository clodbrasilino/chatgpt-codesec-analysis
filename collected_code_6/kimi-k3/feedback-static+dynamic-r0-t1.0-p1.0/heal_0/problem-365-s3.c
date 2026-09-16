#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int count_digits(long long number) {
    int count = 0;
    
    if (number == 0) {
        return 1;
    }
    
    if (number < 0) {
        if (number == LLONG_MIN) {
            number = LLONG_MAX;
        } else {
            number = -number;
        }
    }
    
    while (number != 0) {
        number /= 10;
        count++;
    }
    
    return count;
}

int main(void) {
    long long number;
    
    printf("Enter a number: ");
    
    if (scanf("%lld", &number) != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("Number of digits: %d\n", count_digits(number));
    
    return EXIT_SUCCESS;
}