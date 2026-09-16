#include <stdio.h>
#include <stdlib.h>

long long get_lucas_number(int n) {
    if (n < 0) {
        return -1;
    }
    
    if (n == 0) {
        return 2;
    }
    if (n == 1) {
        return 1;
    }

    long long prev2 = 2;
    long long prev1 = 1;
    long long current = 0;

    for (int i = 2; i <= n; i++) {
        current = prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }

    return current;
}

int main(void) {
    int n = 10;
    long long result = get_lucas_number(n);
    
    if (result != -1) {
        printf("The %d'th Lucas number is: %lld\n", n, result);
    } else {
        printf("Invalid input. n must be a non-negative integer.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}