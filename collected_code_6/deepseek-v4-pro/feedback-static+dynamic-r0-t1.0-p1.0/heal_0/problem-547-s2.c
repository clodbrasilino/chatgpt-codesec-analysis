#include <stdio.h>
#include <stdlib.h>

int hamming_distance(int a, int b) {
    int xor_result = a ^ b;
    int count = 0;
    while (xor_result) {
        count += xor_result & 1;
        xor_result >>= 1;
    }
    return count;
}

int sum_hamming_distances(int n) {
    if (n < 0) {
        return -1;
    }
    
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += hamming_distance(i, i + 1);
    }
    return total;
}

int main(void) {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (n < 0) {
        fprintf(stderr, "n must be non-negative\n");
        return 1;
    }
    
    int result = sum_hamming_distances(n);
    printf("Sum of hamming distances: %d\n", result);
    
    return 0;
}