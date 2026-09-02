#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    if (b == 0) {
        return abs(a);
    }
    return gcd(b, a % b);
}

int main(int argc, const char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <integer1> <integer2>\n", argv[0]);
        return 1;
    }

    char *endptr1;
    char *endptr2;
    long num1 = strtol(argv[1], &endptr1, 10);
    long num2 = strtol(argv[2], &endptr2, 10);

    if (*endptr1 != '\0' || *endptr2 != '\0') {
        fprintf(stderr, "Error: Arguments must be valid integers.\n");
        return 1;
    }

    printf("%d\n", gcd((int)num1, (int)num2));

    return 0;
}