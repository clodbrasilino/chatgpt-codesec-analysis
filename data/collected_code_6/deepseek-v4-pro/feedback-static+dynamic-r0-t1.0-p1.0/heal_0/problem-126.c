#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int sum_common_divisors(int a, int b) {
    if (a <= 0 || b <= 0) {
        return 0;
    }

    int g = gcd(a, b);
    int sum = 0;

    for (int i = 1; i * i <= g; i++) {
        if (g % i == 0) {
            sum += i;
            if (i != g / i) {
                sum += g / i;
            }
        }
    }

    return sum;
}

int main(void) {
    int num1, num2;
    printf("Enter two positive integers: ");
    if (scanf("%d %d", &num1, &num2) != 2) {
        printf("Invalid input.\n");
        return 1;
    }

    int result = sum_common_divisors(num1, num2);
    printf("Sum of common divisors: %d\n", result);

    return 0;
}