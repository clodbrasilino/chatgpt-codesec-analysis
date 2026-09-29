#include <stdio.h>
#include <stdlib.h>

static int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

static int sum_common_divisors(int num1, int num2) {
    if (num1 <= 0 || num2 <= 0)
        return -1;

    int g = gcd(num1, num2);
    int sum = 0;

    for (int i = 1; i * i <= g; i++) {
        if (g % i == 0) {
            sum += i;
            if (i != g / i)
                sum += g / i;
        }
    }

    return sum;
}

int main(void) {
    int a, b;

    printf("Enter two positive integers: ");
    if (scanf("%d %d", &a, &b) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    int result = sum_common_divisors(a, b);
    if (result == -1) {
        fprintf(stderr, "Numbers must be positive\n");
        return EXIT_FAILURE;
    }

    printf("Sum of common divisors: %d\n", result);
    return EXIT_SUCCESS;
}