#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <limits.h>

bool is_even(int number) {
    return (number % 2) == 0;
}

int main(int argc, const char *const argv[]) {
    if (argc < 2) {
        return 1;
    }

    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);

    if (errno == ERANGE || val < INT_MIN || val > INT_MAX || endptr == argv[1] || *endptr != '\0') {
        return 1;
    }

    int test_number = (int)val;
    
    if (is_even(test_number)) {
        printf("%d is even.\n", test_number);
    } else {
        printf("%d is odd.\n", test_number);
    }
    
    return 0;
}