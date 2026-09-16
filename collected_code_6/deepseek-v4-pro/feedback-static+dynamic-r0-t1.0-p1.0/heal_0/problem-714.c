#include <stdio.h>

int countDistinctPrimeFactors(int n) {
    int count = 0;

    if (n < 2) {
        return 0;
    }

    if (n % 2 == 0) {
        count++;
        while (n % 2 == 0) {
            n /= 2;
        }
    }

    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            count++;
            while (n % i == 0) {
                n /= i;
            }
        }
    }

    if (n > 2) {
        count++;
    }

    return count;
}

int main() {
    int num;

    printf("Enter a number: ");
    if (scanf("%d", &num) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    printf("Number of distinct prime factors: %d\n", countDistinctPrimeFactors(num));

    return 0;
}