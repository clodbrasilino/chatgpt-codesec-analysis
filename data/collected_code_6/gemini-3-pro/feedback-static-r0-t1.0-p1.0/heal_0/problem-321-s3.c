#include <stdio.h>
#include <stdlib.h>

unsigned long long get_demlo_number(int n);

unsigned long long get_demlo_number(int n) {
    unsigned long long repunit = 0;
    
    if (n < 1 || n > 9) {
        return 0;
    }
    
    for (int i = 0; i < n; i++) {
        repunit = repunit * 10ULL + 1ULL;
    }
    
    return repunit * repunit;
}

int main(void) {
    int n = 0;
    unsigned long long result = 0;
    
    if (scanf("%d", &n) != 1) {
        return EXIT_FAILURE;
    }
    
    if (n < 1 || n > 9) {
        return EXIT_FAILURE;
    }
    
    result = get_demlo_number(n);
    
    if (printf("%llu\n", result) < 0) {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}