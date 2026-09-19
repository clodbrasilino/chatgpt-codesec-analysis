#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

bool have_opposite_signs(int a, int b) {
    if (a == 0 || b == 0) {
        return (a != 0) || (b != 0);
    }
    return ((a ^ b) < 0);
}

int main(int argc, char * const argv[const]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <int1> <int2>\n", argv[0]);
        return 1;
    }

    long la, lb;
    char *endptr1, *endptr2;

    la = strtol(argv[1], &endptr1, 10);
    if (*endptr1 != '\0' || la < INT_MIN || la > INT_MAX) {
        fprintf(stderr, "Invalid integer: %s\n", argv[1]);
        return 1;
    }

    lb = strtol(argv[2], &endptr2, 10);
    if (*endptr2 != '\0' || lb < INT_MIN || lb > INT_MAX) {
        fprintf(stderr, "Invalid integer: %s\n", argv[2]);
        return 1;
    }

    int a = (int)la;
    int b = (int)lb;

    printf("%s\n", have_opposite_signs(a, b) ? "True" : "False");
    return 0;
}