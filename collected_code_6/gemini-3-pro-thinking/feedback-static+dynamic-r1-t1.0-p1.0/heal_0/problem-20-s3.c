#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

bool is_woodall(unsigned long long num);

bool is_woodall(unsigned long long num) {
    if (num < 1) {
        return false;
    }

    unsigned long long n = 1;
    
    while (n < 64) {
        unsigned long long power_of_two = 1ULL << n;
        
        if (ULLONG_MAX / power_of_two < n) {
            break;
        }
        
        unsigned long long w = n * power_of_two - 1;
        
        if (w == num) {
            return true;
        }
        
        if (w > num) {
            break;
        }
        
        n++;
    }
    
    return false;
}

int main(void) {
    unsigned long long input_number = 0;

    if (scanf("%llu", &input_number) != 1) {
        return EXIT_FAILURE;
    }

    if (is_woodall(input_number)) {
        printf("Woodall\n");
    } else {
        printf("Not Woodall\n");
    }

    return EXIT_SUCCESS;
}