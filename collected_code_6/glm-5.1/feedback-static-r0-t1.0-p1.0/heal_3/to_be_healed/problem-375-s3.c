#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int round_to_nearest_multiple(int num, int multiple) {
    if (multiple == 0) {
        return 0;
    }

    int quotient = num / multiple;
    int remainder = num % multiple;

    if (num < 0 && remainder != 0) {
        quotient -= 1;
        remainder = num - (quotient * multiple);
    }

    if (abs(remainder) >= abs(multiple) - abs(remainder)) {
        if ((num < 0 && multiple > 0) || (num > 0 && multiple < 0)) {
            return (quotient - 1) * multiple;
        } else {
            return (quotient + 1) * multiple;
        }
    }

    return quotient * multiple;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 3) {
        return EXIT_FAILURE;
    }

    char *endptr1;
    char *endptr2;
    long val1 = strtol(argv[1], &endptr1, 10);
    long val2 = strtol(argv[2], &endptr2, 10);

    if (*endptr1 != '\0' || *endptr2 != '\0' || val2 == 0 ||
        val1 < INT_MIN || val1 > INT_MAX || val2 < INT_MIN || val2 > INT_MAX) {
        return EXIT_FAILURE;
    }

    int num = (int)val1;
    int multiple = (int)val2;
    int result = round_to_nearest_multiple(num, multiple);

    printf("%d\n", result);

    return EXIT_SUCCESS;
}