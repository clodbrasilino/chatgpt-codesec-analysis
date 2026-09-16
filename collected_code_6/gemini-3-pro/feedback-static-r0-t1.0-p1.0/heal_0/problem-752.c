#include <stdio.h>
#include <stdlib.h>

int get_jacobsthal(int n, unsigned long long *result) {
    if (n < 0 || result == NULL) {
        return -1;
    }

    if (n == 0) {
        *result = 0;
        return 0;
    }
    if (n == 1) {
        *result = 1;
        return 0;
    }

    unsigned long long prev2 = 0;
    unsigned long long prev1 = 1;
    unsigned long long current = 0;

    for (int i = 2; i <= n; i++) {
        unsigned long long term = 2 * prev2;
        if (term < prev2) {
            return -2;
        }
        
        current = prev1 + term;
        if (current < prev1) {
            return -2; 
        }
        
        prev2 = prev1;
        prev1 = current;
    }

    *result = current;
    return 0;
}

int main(void) {
    int n = 15;
    unsigned long long result = 0;

    int status = get_jacobsthal(n, &result);

    if (status == 0) {
        printf("%llu\n", result);
    } else if (status == -1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    } else if (status == -2) {
        fprintf(stderr, "Integer overflow occurred.\n");
        return EXIT_FAILURE;
    } else {
        fprintf(stderr, "Unknown error.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}