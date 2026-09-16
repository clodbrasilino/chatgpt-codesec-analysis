#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <stdbool.h>

static bool is_odd(int number) {
    return (number & 1) != 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input_str = argv[1];
    char *endptr;
    errno = 0;
    long input = strtol(input_str, &endptr, 10);

    if (errno == ERANGE || *endptr != '\0' || endptr == input_str) {
        fprintf(stderr, "Error: Invalid integer input.\n");
        return EXIT_FAILURE;
    }

    if (input > INT_MAX || input < INT_MIN) {
        fprintf(stderr, "Error: Integer out of range.\n");
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