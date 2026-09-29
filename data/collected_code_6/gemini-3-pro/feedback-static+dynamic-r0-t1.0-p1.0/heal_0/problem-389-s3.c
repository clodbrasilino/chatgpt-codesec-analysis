#include <stdio.h>
#include <stdlib.h>

unsigned long long get_lucas_number(unsigned int n, int *error_flag) {
    if (error_flag != NULL) {
        *error_flag = 0;
    }

    if (n == 0) {
        return 2;
    }
    if (n == 1) {
        return 1;
    }

    unsigned long long prev2 = 2;
    unsigned long long prev1 = 1;
    unsigned long long current = 0;

    for (unsigned int i = 2; i <= n; i++) {
        current = prev2 + prev1;
        
        if (current < prev2) {
            if (error_flag != NULL) {
                *error_flag = 1;
            }
            return 0;
        }
        
        prev2 = prev1;
        prev1 = current;
    }

    return current;
}

int main(void) {
    unsigned int n = 50;
    int error = 0;
    
    unsigned long long lucas_number = get_lucas_number(n, &error);

    if (error != 0) {
        fprintf(stderr, "Error: Integer overflow computing Lucas number for n=%u\n", n);
        return EXIT_FAILURE;
    }

    printf("%llu\n", lucas_number);

    return EXIT_SUCCESS;
}