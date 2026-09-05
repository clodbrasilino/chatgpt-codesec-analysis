#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int is_perfect_square(long long num) {
    if (num < 0) {
        return 0;
    }
    if (num == 0) {
        return 1;
    }
    long long root = (long long)round(sqrt((double)num));
    if (root * root == num) {
        return 1;
    }
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    long long val = strtoll(argv[1], &endptr, 10);
    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (is_perfect_square(val)) {
        printf("%lld is a perfect square\n", val);
    } else {
        printf("%lld is not a perfect square\n", val);
    }
    return EXIT_SUCCESS;
}