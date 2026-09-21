#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int perrin(int n) {
    int a = 3, b = 0, c = 2;
    if (n == 1) return a;
    if (n == 2) return b;
    if (n == 3) return c;
    for (int i = 4; i <= n; i++) {
        int next = a + b;
        a = b;
        b = c;
        c = next;
    }
    return c;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (endptr == argv[1] || *endptr != '\0' || val <= 0 || val > INT_MAX || errno == ERANGE) {
        return EXIT_FAILURE;
    }
    printf("%d\n", perrin((int)val));
    return EXIT_SUCCESS;
}