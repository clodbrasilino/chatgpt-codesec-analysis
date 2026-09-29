#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int is_odd(int number) {
    return number & 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    long input = strtol(argv[1], &endptr, 10);

    if (errno == ERANGE || input > INT_MAX || input < INT_MIN) {
        fprintf(stderr, "Error: Integer out of range.\n");
        return EXIT_FAILURE;
    }

    if (endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Error: Invalid integer input.\n");
        return EXIT_FAILURE;
    }

    int number = (int)input;

    if (is_odd(number)) {
        printf("%d is odd.\n", number);
    } else {
        printf("%d is even.\n", number);
    }

    return EXIT_SUCCESS;
}