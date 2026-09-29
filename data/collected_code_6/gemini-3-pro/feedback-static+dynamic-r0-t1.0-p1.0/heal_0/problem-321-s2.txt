#include <stdio.h>
#include <stdlib.h>

unsigned long long calculate_demlo(int n) {
    if (n < 1 || n > 9) {
        return 0;
    }
    
    unsigned long long ones = 0;
    for (int i = 0; i < n; i++) {
        ones = ones * 10 + 1;
    }
    
    return ones * ones;
}

int main(void) {
    int n;
    
    if (scanf("%d", &n) != 1) {
        return EXIT_FAILURE;
    }
    
    unsigned long long demlo = calculate_demlo(n);
    if (demlo == 0) {
        return EXIT_FAILURE;
    }
    
    printf("%llu\n", demlo);
    
    return EXIT_SUCCESS;
}