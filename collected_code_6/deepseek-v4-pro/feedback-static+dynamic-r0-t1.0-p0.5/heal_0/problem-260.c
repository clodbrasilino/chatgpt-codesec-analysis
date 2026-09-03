#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

bool is_prime(int n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

int nth_newman_shanks_williams_prime(int n) {
    if (n <= 0) {
        fprintf(stderr, "Error: n must be positive\n");
        exit(EXIT_FAILURE);
    }
    
    int count = 0;
    int k = 0;
    int result = 0;
    
    while (count < n) {
        long long s = 2LL * k * k + 2LL * k + 1;
        if (s > 2147483647LL) {
            fprintf(stderr, "Error: value exceeds int range\n");
            exit(EXIT_FAILURE);
        }
        int candidate = (int)s;
        if (is_prime(candidate)) {
            count++;
            result = candidate;
        }
        k++;
    }
    
    return result;
}

int main(void) {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }
    
    int result = nth_newman_shanks_williams_prime(n);
    printf("%d\n", result);
    
    return EXIT_SUCCESS;
}