#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void print_lucky_numbers(int n) {
    if (n <= 0) {
        return;
    }

    int *sieve = malloc((size_t)n * sizeof(int));
    if (sieve == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        sieve[i] = 2 * i + 1;
    }

    int count = n;
    int idx = 1;

    while (idx < count) {
        int step = sieve[idx];
        int write_idx = idx;
        
        for (int read_idx = idx; read_idx < count; read_idx++) {
            if ((read_idx + 1) % step != 0) {
                sieve[write_idx++] = sieve[read_idx];
            }
        }
        count = write_idx;
        idx++;
    }

    for (int i = 0; i < count; i++) {
        printf("%d ", sieve[i]);
    }
    printf("\n");

    free(sieve);
}

int main(void) {
    int n;
    
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    print_lucky_numbers(n);
    
    return EXIT_SUCCESS;
}