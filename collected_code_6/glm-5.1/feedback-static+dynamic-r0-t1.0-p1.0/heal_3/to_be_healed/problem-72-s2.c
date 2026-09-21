#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int can_be_diff_of_squares(long long n) {
    if (n < 0) {
        n = -n;
    }
    return (n % 4 != 2);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *endptr;
    long long val = strtoll(argv[1], &endptr, 10);

    if (*endptr != '\0' || errno == ERANGE) {
        fprintf(stderr, "Invalid input or out of range\n");
        return EXIT_FAILURE;
    }

    if (can_be_diff_of_squares(val)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return EXIT_SUCCESS;
}