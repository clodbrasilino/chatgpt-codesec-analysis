#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int find_factorial_divisible(long long x) {
    if (x <= 0) {
        return -1;
    }
    int n = 1;
    long long factorial = 1;
    while (factorial % x != 0) {
        n++;
        if (n > 20) {
            return -1;
        }
        if (factorial > LLONG_MAX / n) {
            return -1;
        }
        factorial *= n;
    }
    return n;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        return 1;
    }
    char *endptr;
    errno = 0;
    long long val = strtoll(argv[1], &endptr, 10);
    if (endptr == argv[1] || *endptr != '\0' || errno == ERANGE || val <= 0) {
        return 1;
    }
    long long x = val;
    int result = find_factorial_divisible(x);
    if (result == -1) {
        return 1;
    }
    printf("%d\n", result);
    return 0;
}