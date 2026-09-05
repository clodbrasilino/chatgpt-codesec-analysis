#include <stdio.h>
#include <stdbool.h>

bool have_opposite_signs(int a, int b) {
    return ((a ^ b) < 0);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <int1> <int2>\n", argv[0]);
        return 1;
    }

    int a, b;
    if (sscanf(argv[1], "%d", &a) != 1) {
        fprintf(stderr, "Invalid integer: %s\n", argv[1]);
        return 1;
    }
    if (sscanf(argv[2], "%d", &b) != 1) {
        fprintf(stderr, "Invalid integer: %s\n", argv[2]);
        return 1;
    }

    printf("%s\n", have_opposite_signs(a, b) ? "true" : "false");
    return 0;
}