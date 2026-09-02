#include <stdio.h>
#include <stdlib.h>

int perrin_number(int n) {
    if (n == 0) return 3;
    if (n == 1) return 0;
    if (n == 2) return 2;
    
    int p0 = 3, p1 = 0, p2 = 2;
    for (int i = 3; i <= n; i++) {
        int p3 = p1 + p0;
        p0 = p1;
        p1 = p2;
        p2 = p3;
    }
    return p2;
}

long long sum_perrin_numbers(int n) {
    if (n < 0) return 0;
    
    long long sum = 0;
    if (n >= 0) sum += 3;
    if (n >= 1) sum += 0;
    if (n >= 2) sum += 2;
    
    if (n < 3) return sum;
    
    int p0 = 3, p1 = 0, p2 = 2;
    for (int i = 3; i <= n; i++) {
        int p3 = p1 + p0;
        sum += p3;
        p0 = p1;
        p1 = p2;
        p2 = p3;
    }
    return sum;
}

int main(int argc, char *const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    char *endptr;
    long n = strtol(argv[1], &endptr, 10);
    
    if (*endptr != '\0' || n < 0 || n > 1000000) {
        fprintf(stderr, "Error: n must be a non-negative integer\n");
        return EXIT_FAILURE;
    }
    
    long long result = sum_perrin_numbers((int)n);
    printf("Sum of Perrin numbers up to %ld: %lld\n", n, result);
    
    return EXIT_SUCCESS;
}