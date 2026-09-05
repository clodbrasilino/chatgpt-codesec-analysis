#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    if (b == 0) {
        if (a < 0) {
            return -a;
        }
        return a;
    }
    return gcd(b, a % b);
}

int main(int argc, char *argv[]) {
    int num1, num2;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <integer1> <integer2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (sscanf(argv[1], "%d", &num1) != 1) {
        fprintf(stderr, "Invalid input for integer1\n");
        return EXIT_FAILURE;
    }

    if (sscanf(argv[2], "%d", &num2) != 1) {
        fprintf(stderr, "Invalid input for integer2\n");
        return EXIT_FAILURE;
    }

    if (num1 == 0 && num2 == 0) {
        fprintf(stderr, "GCD is undefined for 0 and 0\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", gcd(num1, num2));

    return EXIT_SUCCESS;
}