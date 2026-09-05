#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <limits.h>

int find_sqrt_perfect(int number, int *result) {
    if (result == NULL) {
        return -1;
    }

    if (number < 0) {
        return -1;
    }

    errno = 0;
    double root = sqrt((double)number);
    if (errno != 0) {
        return -1;
    }

    double floor_val = floor(root);
    if (floor_val * floor_val == (double)number) {
        *result = (int)floor_val;
        return 0;
    }

    return -1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);

    if (errno != 0 || endptr == argv[1] || *endptr != '\0' || val < 0 || val > INT_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    int result;
    if (find_sqrt_perfect((int)val, &result) == 0) {
        printf("%d\n", result);
        return EXIT_SUCCESS;
    } else {
        fprintf(stderr, "Not a perfect square\n");
        return EXIT_FAILURE;
    }
}