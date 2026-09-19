#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int count_digits(long long n) {
    if (n == 0) {
        return 1;
    }
    if (n == LLONG_MIN) {
        return 19;
    }
    if (n < 0) {
        n = -n;
    }
    int count = 0;
    while (n > 0) {
        count++;
        n /= 10;
    }
    return count;
}

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    errno = 0;
    long long num = strtoll(argv[1], &endptr, 10);
    if (errno != 0 || *endptr != '\0' || argv[1] == endptr) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    printf("%d\n", count_digits(num));
    return EXIT_SUCCESS;
}