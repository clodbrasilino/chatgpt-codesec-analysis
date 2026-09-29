#include <stdio.h>
#include <stdlib.h>

long long sum_of_divisors(int n) {
    if (n <= 0) {
        return 0;
    }

    long long sum = 0;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i) {
                sum += n / i;
            }
        }
    }
    return sum;
}

int main(void) {
    int number;
    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("Sum of divisors: %lld\n", sum_of_divisors(number));
    return EXIT_SUCCESS;
}