#include <stdio.h>
#include <stdlib.h>

int sum_common_divisors(int a, int b) {
    if (a <= 0 || b <= 0) {
        return -1;
    }

    int min = a < b ? a : b;
    int sum = 0;

    for (int i = 1; i <= min; i++) {
        if (a % i == 0 && b % i == 0) {
            sum += i;
        }
    }

    return sum;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    int a, b;

    if (argc == 3) {
        a = strtol(argv[1], NULL, 10);
        b = strtol(argv[2], NULL, 10);
    } else {
        if (scanf("%d %d", &a, &b) != 2) {
            return 1;
        }
    }

    int result = sum_common_divisors(a, b);

    if (result < 0) {
        return 1;
    }

    printf("%d\n", result);

    return 0;
}