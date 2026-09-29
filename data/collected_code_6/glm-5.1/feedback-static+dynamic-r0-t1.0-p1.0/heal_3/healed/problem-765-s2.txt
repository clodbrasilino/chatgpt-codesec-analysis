#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

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
        if (result == ULLONG_MAX) {
            break;
        }
        result++;
    }
    return result;
}

int main(int argc, char * const argv[const]) {
    int n = 5;
    if (argc > 1) {
        char *endptr;
        errno = 0;
        long val = strtol(argv[1], &endptr, 10);
        if (endptr == argv[1] || *endptr != '\0' || val < 0 || val > INT_MAX || errno != 0) {
            return EXIT_FAILURE;
        }
        n = (int)val;
    }
    unsigned long long num = find_nth_polite_number(n);
    printf("%llu\n", num);
    return EXIT_SUCCESS;
}