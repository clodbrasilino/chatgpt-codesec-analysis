#include <stdio.h>
#include <stdlib.h>

int abs_val(int x) {
    return x < 0 ? -x : x;
}

int min_operations(int a, int b) {
    if (a < 0 || b < 0) {
        return -1;
    }
    return abs_val(a - b);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <num1> <num2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr1, *endptr2;
    long val1 = strtol(argv[1], &endptr1, 10);
    long val2 = strtol(argv[2], &endptr2, 10);

    if (*endptr1 != '\0' || *endptr2 != '\0' || val1 < 0 || val2 < 0) {
        fprintf(stderr, "Error: Invalid input. Positive integers required.\n");
        return EXIT_FAILURE;
    }

    int result = min_operations((int)val1, (int)val2);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}