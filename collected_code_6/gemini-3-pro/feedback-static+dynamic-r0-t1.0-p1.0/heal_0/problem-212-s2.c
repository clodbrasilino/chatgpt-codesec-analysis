#include <stdio.h>
#include <stdlib.h>

unsigned long long sum_of_fourth_powers(int n) {
    if (n < 0) {
        return 0;
    }
    
    unsigned long long sum = 0;
    for (int i = 1; i <= n; i++) {
        unsigned long long square = (unsigned long long)i * i;
        sum += square * square;
    }
    
    return sum;
}

int main(void) {
    int n;
    
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 0) {
        fprintf(stderr, "Input must depend on natural numbers\n");
        return EXIT_FAILURE;
    }
    
    unsigned long long result = sum_of_fourth_powers(n);
    printf("%llu\n", result);
    
    return EXIT_SUCCESS;
}