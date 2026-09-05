#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    int temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int are_coprime(int a, int b) {
    if (a == 0 && b == 0) {
        return 0;
    }
    int abs_a = a < 0 ? -a : a;
    int abs_b = b < 0 ? -b : b;
    return gcd(abs_a, abs_b) == 1;
}

int main(int argc, char *argv[]) {
    int a, b;
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <integer1> <integer2>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    char *endptr1, *endptr2;
    long val1 = strtol(argv[1], &endptr1, 10);
    long val2 = strtol(argv[2], &endptr2, 10);
    
    if (*endptr1 != '\0' || *endptr2 != '\0') {
        fprintf(stderr, "Invalid input: arguments must be integers\n");
        return EXIT_FAILURE;
    }
    
    if (val1 < INT_MIN || val1 > INT_MAX || val2 < INT_MIN || val2 > INT_MAX) {
        fprintf(stderr, "Invalid input: integer overflow\n");
        return EXIT_FAILURE;
    }
    
    a = (int)val1;
    b = (int)val2;
    
    if (are_coprime(a, b)) {
        printf("%d and %d are co-prime\n", a, b);
    } else {
        printf("%d and %d are not co-prime\n", a, b);
    }
    
    return EXIT_SUCCESS;
}