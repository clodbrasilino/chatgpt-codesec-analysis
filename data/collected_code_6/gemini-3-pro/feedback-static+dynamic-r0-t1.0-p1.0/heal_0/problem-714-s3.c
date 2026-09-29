#include <stdio.h>
#include <stdlib.h>

int countDistinctPowerOfPrimeFactors(unsigned int n) {
    if (n == 0) {
        return 0;
    }

    int distinct_count = 0;
    unsigned int current_n = n;

    for (unsigned int i = 2; i * i <= current_n; i++) {
        if (current_n % i == 0) {
            distinct_count++;
            while (current_n % i == 0) {
                current_n /= i;
            }
        }
    }

    if (current_n > 1) {
        distinct_count++;
    }

    return distinct_count;
}

int main(void) {
    unsigned int num = 0;
    
    if (scanf("%u", &num) != 1) {
        return EXIT_FAILURE;
    }

    int result = countDistinctPowerOfPrimeFactors(num);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}