#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int is_even(int num) {
    return (num & 1) == 0;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);

    if (errno == ERANGE || endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Error: Invalid integer format or out of range.\n");
        return EXIT_FAILURE;
    }

    if (val < INT_MIN || val > INT_MAX) {
        fprintf(stderr, "Error: Integer out of range.\n");
        return EXIT_FAILURE;
    }

    int num = (int)val;

    if (is_even(num)) {
        printf("%d is even\n", num);
    } else {
        printf("%d is odd\n", num);
    }

    return EXIT_SUCCESS;
}