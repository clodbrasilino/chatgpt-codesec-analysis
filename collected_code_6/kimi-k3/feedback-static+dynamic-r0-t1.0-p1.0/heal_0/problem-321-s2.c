#include <stdio.h>
#include <stdlib.h>

long long find_demlo_number(int n) {
    if (n < 1 || n > 9) {
        return -1;
    }
    
    long long result = 0;
    int i;
    
    for (i = 1; i <= n; i++) {
        result = result * 10 + i;
    }
    
    for (i = n - 1; i >= 1; i--) {
        result = result * 10 + i;
    }
    
    return result;
}

int main(void) {
    int n;
    long long demlo;
    
    printf("Enter a number (1-9): ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    demlo = find_demlo_number(n);
    
    if (demlo == -1) {
        fprintf(stderr, "Number must be between 1 and 9\n");
        return EXIT_FAILURE;
    }
    
    printf("Demlo number: %lld\n", demlo);
    
    return EXIT_SUCCESS;
}