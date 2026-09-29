#include <stdio.h>
#include <stdlib.h>

unsigned int find_gcd(unsigned int a, unsigned int b) {
    if (a == 0 || b == 0) {
        return a + b;
    }
    
    while (b != 0) {
        unsigned int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main(int argc, const char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <positive_integer1> <positive_integer2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr1;
    char *endptr2;
    
    long int num1 = strtol(argv[1], &endptr1, 10);
    long int num2 = strtol(argv[2], &endptr2, 10);

    if (*endptr1 != '\0' || *endptr2 != '\0' || num1 <= 0 || num2 <= 0) {
        fprintf(stderr, "Error: Both arguments must be perfectly parsed positive integers.\n");
        return EXIT_FAILURE;
    }

    unsigned int a = (unsigned int)num1;
    unsigned int b = (unsigned int)num2;

    unsigned int gcd = find_gcd(a, b);

    printf("%u\n", gcd);

    return EXIT_SUCCESS;
}