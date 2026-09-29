#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    a = abs(a);
    b = abs(b);
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int main(int argc, char * const * const argv) {
    int num1, num2;
    long temp;
    char *endptr1, *endptr2;

    if (argc != 3) {
        return EXIT_FAILURE;
    }

    temp = strtol(argv[1], &endptr1, 10);
    if (*endptr1 != '\0' || endptr1 == argv[1] || temp < INT_MIN || temp > INT_MAX) {
        return EXIT_FAILURE;
    }
    num1 = (int)temp;

    temp = strtol(argv[2], &endptr2, 10);
    if (*endptr2 != '\0' || endptr2 == argv[2] || temp < INT_MIN || temp > INT_MAX) {
        return EXIT_FAILURE;
    }
    num2 = (int)temp;

    int result = gcd(num1, num2);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}