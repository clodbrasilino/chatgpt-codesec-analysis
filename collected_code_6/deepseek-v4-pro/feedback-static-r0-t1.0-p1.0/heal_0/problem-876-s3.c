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

int lcm(int a, int b) {
    if (a <= 0 || b <= 0) {
        return 0;
    }
    return (a / gcd(a, b)) * b;
}

int main(void) {
    int num1, num2;
    int result;

    printf("Enter two positive integers: ");
    if (scanf("%d %d", &num1, &num2) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    result = lcm(num1, num2);
    if (result == 0) {
        fprintf(stderr, "LCM is undefined for non-positive integers\n");
        return EXIT_FAILURE;
    }

    printf("LCM of %d and %d is %d\n", num1, num2, result);
    return EXIT_SUCCESS;
}