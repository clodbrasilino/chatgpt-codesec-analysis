#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int lcm(int a, int b) {
    return (a / gcd(a, b)) * b;
}

int pow_mod(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int last_digit_factorial_division(int a, int b) {
    int lastDigitA = 1, lastDigitB = 1;
    for (int i = 2; i <= a; ++i) {
        lastDigitA = (lastDigitA * (i % 10)) % 10;
    }
    for (int i = a + 1; i <= b; ++i) {
        lastDigitB = (lastDigitB * (i % 10)) % 10;
    }
    if (lastDigitA == 0 || lastDigitB == 0) {
        return 0;
    }
    int inverse = pow_mod(lastDigitA, 8, 10);
    return (lastDigitB * inverse) % 10;
}

int main() {
    int a, b;
    printf("Enter two integers a and b: ");
    if (scanf("%d %d", &a, &b) != 2 || a < 0 || b < 0) {
        printf("Invalid input.\n");
        return EXIT_FAILURE;
    }
    if (a > b) {
        printf("a should be less than or equal to b.\n");
        return EXIT_FAILURE;
    }
    int result = last_digit_factorial_division(a, b);
    printf("The last digit of factorial(b) divided by factorial(a) is: %d\n", result);
    return EXIT_SUCCESS;
}