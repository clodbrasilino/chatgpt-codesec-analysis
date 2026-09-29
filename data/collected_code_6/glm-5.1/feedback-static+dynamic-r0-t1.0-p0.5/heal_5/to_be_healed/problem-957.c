#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int get_rightmost_set_bit(int n) {
    if (n == 0) {
        return -1;
    }
    return n & (-n);
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

    long num;
    char *endptr;
    errno = 0;
    num = strtol(argv[1], &endptr, 10);

    if (endptr == argv[1] || *endptr != '\0' || errno == ERANGE || num < INT_MIN || num > INT_MAX) {
        fprintf(stderr, "Invalid integer input\n");
        return EXIT_FAILURE;
    }

    int pos = get_rightmost_set_bit((int)num);
    if (pos == -1) {
        printf("0\n");
    } else {
        printf("%d\n", pos);
    }
    return EXIT_SUCCESS;
}