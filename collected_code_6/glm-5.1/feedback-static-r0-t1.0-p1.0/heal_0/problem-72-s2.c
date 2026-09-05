#include <stdio.h>
#include <stdlib.h>

int can_be_diff_of_squares(long long n) {
    if (n < 0) {
        n = -n;
    }
    return (n % 4 != 2);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }

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