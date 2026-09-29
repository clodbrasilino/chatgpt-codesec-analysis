#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1, got 2
  *  test case 1 failed: expected 4, got 6
  */

int min_operations(int a, int b) {
    if (a < 0 || b < 0) {
        return -1;
    }
    int diff = a > b ? a - b : b - a;
    return diff;
}

int main(int argc, char const * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <num1> <num2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr1, *endptr2;
    long val1 = strtol(argv[1], &endptr1, 10);
    long val2 = strtol(argv[2], &endptr2, 10);

    if (*endptr1 != '\0' || *endptr2 != '\0' || val1 < 0 || val2 > INT_MAX) {
        fprintf(stderr, "Error: Invalid input. Positive integers required.\n");
        return EXIT_FAILURE;
    }

    int result = min_operations((int)val1, (int)val2);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}