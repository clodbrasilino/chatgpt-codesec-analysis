#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <stdbool.h>

bool str_to_int(const char *str, int *out) {
    char *endptr;
    long val;
    errno = 0;
    val = strtol(str, &endptr, 10);
    if (errno == ERANGE || val > INT_MAX || val < INT_MIN) {
        return false;
    }
    if (endptr == str || *endptr != '\0') {
        return false;
    }
    *out = (int)val;
    return true;
}

int find_closest_smaller(int n) {
    if (n > INT_MIN) {
        return n - 1;
    }
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
    int n;
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    if (!str_to_int(argv[1], &n)) {
        return EXIT_FAILURE;
    }
    int result = find_closest_smaller(n);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}