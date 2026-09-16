#include <stdio.h>
#include <stdlib.h>

int countDistinctPowerOfPrimeFactors(int n) {
    if (n <= 1) {
        return 0;
    }

    int count = 0;
    int power = 0;

    while (n % 2 == 0) {
        power++;
        n /= 2;
    }
    if (power > 0) {
        count++;
    }

    for (int i = 3; i * i <= n; i += 2) {
        power = 0;
        while (n % i == 0) {
            power++;
            n /= i;
        }
        if (power > 0) {
            count++;
        }
    }

    if (n > 2) {
        count++;
    }

    return count;
}

int main(void) {
    int num = 0;

    if (scanf("%d", &num) != 1) {
        return EXIT_FAILURE;
    }

    if (num < 1) {
        return EXIT_FAILURE;
    }

    int result = countDistinctPowerOfPrimeFactors(num);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}