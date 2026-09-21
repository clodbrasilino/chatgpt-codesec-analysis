#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int is_perfect_square(long long num) {
    if (num < 0) {
        return 0;
    }
    if (num == 0) {
        return 1;
    }
    long long root = (long long)round(sqrt((double)num));
    if (root * root == num) {
        return 1;
    }
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        return 0;
    }
    char *endptr;
    long long val = strtoll(argv[1], &endptr, 10);
    if (*endptr != '\0') {
        return 0;
    }
    int result = is_perfect_square(val);
    if (result) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    return 0;
}