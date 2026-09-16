#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

unsigned long long lcm(int a, int b) {
    if (a <= 0 || b <= 0) {
        return 0;
    }
    return ((unsigned long long)a / gcd(a, b)) * b;
}

int main(void) {
    int num1, num2;
    unsigned long long result;

    if (scanf("%d %d", &num1, &num2) != 2) {
        return EXIT_FAILURE;
    }

    result = lcm(num1, num2);

    if (result == 0) {
        return EXIT_FAILURE;
    }

    printf("%llu\n", result);

    return EXIT_SUCCESS;
}