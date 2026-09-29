#include <stdio.h>
#include <stdlib.h>

int is_polite(unsigned long long num) {
    return (num & (num + 1)) != 0;
}

unsigned long long nth_polite(int n) {
    if (n <= 0) {
        return 0;
    }
    
    unsigned long long count = 0;
    unsigned long long num = 1;
    
    while (1) {
        if (is_polite(num)) {
            count++;
            if (count == (unsigned long long)n) {
                return num;
            }
        }
        num++;
    }
}

int main(void) {
    int n;
    
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n <= 0) {
        fprintf(stderr, "n must be positive\n");
        return EXIT_FAILURE;
    }
    
    printf("%llu\n", nth_polite(n));
    
    return EXIT_SUCCESS;
}