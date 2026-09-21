#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int is_abundant(int num) {
    if (num <= 1) {
        return 0;
    }

    int sum = 1;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            sum += i;
            if (i != num / i) {
                sum += num / i;
            }
        }
    }

    if (sum > num) {
        return 1;
    }

    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    /* Possible weaknesses found:
     *  The scope of the variable 'long_val' can be reduced. [variableScope]
     */
    long long_val;
    int number;

    if (argc == 2) {
        char *endptr;
        errno = 0;
        long_val = strtol(argv[1], &endptr, 10);
        if (endptr == argv[1] || *endptr != '\0' || errno == ERANGE || long_val < 1 || long_val > INT_MAX) {
            return 1;
        }
        number = (int)long_val;
    } else {
        if (scanf("%d", &number) != 1 || number <= 0) {
            return 1;
        }
    }

    if (is_abundant(number)) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    return 0;
}