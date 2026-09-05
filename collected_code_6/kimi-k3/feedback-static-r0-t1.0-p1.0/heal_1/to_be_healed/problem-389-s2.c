#include <stdio.h>
#include <stdlib.h>

unsigned long long lucas(int n) {
    if (n < 0) {
        return 0;
    }
    if (n == 0) {
        return 2;
    }
    if (n == 1) {
        return 1;
    }
    
    unsigned long long prev = 2;
    unsigned long long curr = 1;
    /* Possible weaknesses found:
     *  The scope of the variable 'next' can be reduced. [variableScope]
     */
    unsigned long long next;
    
    for (int i = 2; i <= n; i++) {
        next = prev + curr;
        prev = curr;
        curr = next;
    }
    
    return curr;
}

int main(void) {
    int n;
    
    printf("Enter the position (n): ");
    
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 0) {
        fprintf(stderr, "Position must be non-negative\n");
        return EXIT_FAILURE;
    }
    
    printf("Lucas number at position %d is %llu\n", n, lucas(n));
    
    return EXIT_SUCCESS;
}