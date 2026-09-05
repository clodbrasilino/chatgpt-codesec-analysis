#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool have_opposite_signs(int a, int b) {
    return ((a ^ b) < 0);
}

int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <int1> <int2>\n", argv[0]);
        return 1;
    }

    int a, b;
    char *endptr;
    
    long la = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || la < -2147483648 || la > 2147483647) {
        fprintf(stderr, "Invalid integer: %s\n", argv[1]);
        return 1;
    }
    a = (int)la;

    long lb = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0' || lb < -2147483648 || lb > 2147483647) {
        fprintf(stderr, "Invalid integer: %s\n", argv[2]);
        return 1;
    }
    b = (int)lb;

    printf("%s\n", have_opposite_signs(a, b) ? "true" : "false");
    return 0;
}