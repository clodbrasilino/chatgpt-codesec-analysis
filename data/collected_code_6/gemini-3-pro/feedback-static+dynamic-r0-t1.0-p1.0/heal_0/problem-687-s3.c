#include <stdio.h>
#include <stdlib.h>

int find_gcd(int a, int b) {
    if (a < 0) {
        a = -a;
    }
    if (b < 0) {
        b = -b;
    }
    if (b == 0) {
        return a;
    }
    return find_gcd(b, a % b);
}

int main(void) {
    int num1;
    int num2;
    int gcd;
    int result;

    result = scanf("%d %d", &num1, &num2);
    if (result != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (num1 == 0 && num2 == 0) {
        fprintf(stderr, "GCD of 0 and 0 is undefined\n");
        return EXIT_FAILURE;
    }

    gcd = find_gcd(num1, num2);
    printf("%d\n", gcd);

    return EXIT_SUCCESS;
}