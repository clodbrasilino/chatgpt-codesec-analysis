#include <stdio.h>
#include <stdlib.h>

unsigned long long calculate_combination(int n, int k) {
    if (k < 0 || k > n) {
        return 0;
    }
    if (k == 0 || k == n) {
        return 1;
    }
    
    unsigned long long result = 1;
    for (int i = 1; i <= k; i++) {
        result = result * (n - i + 1) / i;
    }
    return result;
}

unsigned long long n_th_rencontres(int n) {
    if (n < 0) {
        return 0;
    }
    if (n == 0) {
        return 1;
    }
    if (n == 1) {
        return 0;
    }
    
    unsigned long long *derangements = (unsigned long long *)malloc((n + 1) * sizeof(unsigned long long));
    if (!derangements) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    derangements[0] = 1;
    derangements[1] = 0;
    
    for (int i = 2; i <= n; i++) {
        derangements[i] = (i - 1) * (derangements[i - 1] + derangements[i - 2]);
    }
    
    unsigned long long rencontres_number = 0;
    for (int k = 0; k <= n; k++) {
        unsigned long long comb = calculate_combination(n, k);
        rencontres_number += comb * derangements[n - k];
    }
    
    free(derangements);
    return rencontres_number;
}

unsigned long long rencontres_number_n_k(int n, int k) {
    if (n < 0 || k < 0 || k > n) {
        return 0;
    }
    
    unsigned long long *derangements = (unsigned long long *)malloc((n - k + 1) * sizeof(unsigned long long));
    if (!derangements) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    derangements[0] = 1;
    if (n - k >= 1) {
        derangements[1] = 0;
    }
    
    for (int i = 2; i <= n - k; i++) {
        derangements[i] = (i - 1) * (derangements[i - 1] + derangements[i - 2]);
    }
    
    unsigned long long comb = calculate_combination(n, k);
    unsigned long long result = comb * derangements[n - k];
    
    free(derangements);
    return result;
}

int main(void) {
    int n = 5;
    int k = 2;
    
    unsigned long long r_n_k = rencontres_number_n_k(n, k);
    printf("Rencontres number D(%d, %d) is %llu\n", n, k, r_n_k);
    
    return EXIT_SUCCESS;
}