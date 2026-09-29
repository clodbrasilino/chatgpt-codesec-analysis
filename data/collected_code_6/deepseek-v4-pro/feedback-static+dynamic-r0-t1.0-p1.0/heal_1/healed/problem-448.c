#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

int64_t perrin_sum(int n) {
    if (n < 0) {
        return -1;
    }
    if (n == 0) {
        return 3;
    }
    if (n == 1) {
        return 3;
    }
    if (n == 2) {
        return 5;
    }
    
    int64_t *perrin = (int64_t *)malloc((n + 1) * sizeof(int64_t));
    if (perrin == NULL) {
        return -1;
    }
    
    perrin[0] = 3;
    perrin[1] = 0;
    perrin[2] = 2;
    
    int64_t sum = 5;
    
    for (int i = 3; i <= n; i++) {
        int64_t next = perrin[i - 2] + perrin[i - 3];
        perrin[i] = next;
        sum += perrin[i];
    }
    
    free(perrin);
    return sum;
}

int main(void) {
    int n;
    
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    int64_t result = perrin_sum(n);
    if (result == -1 && n < 0) {
        fprintf(stderr, "Error: n must be non-negative\n");
        return EXIT_FAILURE;
    }
    
    if (result == -1) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    printf("Sum of Perrin numbers up to P(%d) = %" PRId64 "\n", n, result);
    
    return EXIT_SUCCESS;
}