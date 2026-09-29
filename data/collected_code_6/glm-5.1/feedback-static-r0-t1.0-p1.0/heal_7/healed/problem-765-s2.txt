#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

unsigned long long find_nth_polite_number(int n) {
    if (n <= 0) {
        return 0;
    }
    unsigned long long result = 1;
    int count = 0;
    while (1) {
        if ((result & (result - 1)) != 0) {
            count++;
            if (count == n) {
                break;
            }
        }
        result++;
        if (result == 0) {
            break;
        }
    }
    return result;
}

int main(int argc, char * const * const argv) {
    int n = 5;
    if (argc > 1) {
        char *endptr;
        errno = 0;
        long val = strtol(argv[1], &endptr, 10);
        if (errno != 0 || endptr == argv[1] || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
            return EXIT_FAILURE;
        }
        n = (int)val;
    }
    unsigned long long num = find_nth_polite_number(n);
    printf("%llu\n", num);
    return 0;
}