#include <stdio.h>
#include <stdlib.h>

long long rencontres_number(int n) {
    if (n < 0) {
        return -1;
    }
    if (n == 0) {
        return 1;
    }
    if (n == 1) {
        return 0;
    }
    if (n == 2) {
        return 1;
    }
    
    long long prev2 = 1;
    long long prev1 = 0;
    long long current = 1;
    
    for (int i = 3; i <= n; i++) {
        long long next = (i - 1) * (prev1 + prev2);
        prev2 = prev1;
        prev1 = current;
        current = next;
    }
    
    return current;
}

int main(void) {
    int n;
    
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 0) {
        fprintf(stderr, "n must be non-negative\n");
        return EXIT_FAILURE;
    }
    
    long long result = rencontres_number(n);
    printf("R(%d) = %lld\n", n, result);
    
    return EXIT_SUCCESS;
}