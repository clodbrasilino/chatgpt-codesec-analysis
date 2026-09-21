#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int can_be_diff_of_squares(long long n) {
    if (n < 0) {
        n = -n;
    }
    if (n == 0) {
        return 1;
    }
    if (n % 4 == 2) {
        return 0;
    }
    return 1;
}

int main(int argc, char const * const argv[]) {
    long long num;
    char *endptr;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }
    errno = 0;
    num = strtoll(argv[1], &endptr, 10);
    if (errno != 0 || *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (can_be_diff_of_squares(num)) {
        printf("1\n");
    } else {
        printf("0\n");
    }
    return EXIT_SUCCESS;
}