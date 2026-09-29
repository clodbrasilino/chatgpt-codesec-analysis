#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

unsigned long long rencontres_number(int n, int k) {
    if (n < 0 || k < 0 || k > n) {
        return 0;
    }
    if (n == 0 && k == 0) {
        return 1;
    }
    if (n == 1 && k == 0) {
        return 0;
    }
    
    unsigned long long *prev = (unsigned long long *)malloc((k + 1) * sizeof(unsigned long long));
    unsigned long long *curr = (unsigned long long *)malloc((k + 1) * sizeof(unsigned long long));
    
    if (!prev || !curr) {
        free(prev);
        free(curr);
        exit(EXIT_FAILURE);
    }
    
    for (int j = 0; j <= k; j++) {
        prev[j] = 0;
        curr[j] = 0;
    }
    prev[0] = 1;
    
    for (int i = 1; i <= n; i++) {
        int max_sub_k = k > (i - 1) ? (i - 1) : k;
        curr[0] = (i - 1) * (prev[0] + ((max_sub_k >= 1) ? prev[1] : 0));
        for (int j = 1; j <= k; j++) {
            curr[j] = prev[j - 1] + (i - 1) * ((j <= i - 1) ? prev[j] : 0);
        }
        unsigned long long *temp = prev;
        prev = curr;
        curr = temp;
        for (int j = 0; j <= k; j++) {
            curr[j] = 0;
        }
    }
    
    unsigned long long result = prev[k];
    free(prev);
    free(curr);
    return result;
}

int main(int argc, char const *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n> <k>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr_n;
    errno = 0;
    long val_n = strtol(argv[1], &endptr_n, 10);
    if (endptr_n == argv[1] || *endptr_n != '\0' || val_n < 0 || val_n > INT_MAX || errno == ERANGE) {
        fprintf(stderr, "Invalid input for n\n");
        return EXIT_FAILURE;
    }
    int n = (int)val_n;

    char *endptr_k;
    errno = 0;
    long val_k = strtol(argv[2], &endptr_k, 10);
    if (endptr_k == argv[2] || *endptr_k != '\0' || val_k < 0 || val_k > INT_MAX || errno == ERANGE) {
        fprintf(stderr, "Invalid input for k\n");
        return EXIT_FAILURE;
    }
    int k = (int)val_k;

    unsigned long long res = rencontres_number(n, k);
    printf("%llu\n", res);
    return EXIT_SUCCESS;
}