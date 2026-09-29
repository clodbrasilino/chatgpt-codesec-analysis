#include <stdio.h>
#include <stdlib.h>

int find_min_sum_factors(int n) {
    if (n <= 1) {
        return n;
    }

    int min_sum = n + 1;

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            int factor1 = i;
            int factor2 = n / i;
            int current_sum = factor1 + factor2;
            
            if (current_sum < min_sum) {
                min_sum = current_sum;
            }
        }
    }

    if (min_sum == n + 1) {
        return n;
    }

    return min_sum;
}

int main(int argc, char * const argv[]) {
    int n;
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    long val = strtol(argv[1], NULL, 10);
    if (val <= 0 || val > 2147483647) {
        fprintf(stderr, "Invalid input: must be a positive 32-bit integer\n");
        return 1;
    }

    n = (int)val;
    int result = find_min_sum_factors(n);
    printf("%d\n", result);

    return 0;
}