#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 /* Possible weaknesses found:
  *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

int is_armstrong(int num) {
    if (num < 0) {
        return 0;
    }

    int original = num;
    int sum = 0;
    int digits = 0;

    if (num == 0) {
        digits = 1;
    } else {
        int temp = num;
        while (temp > 0) {
            digits++;
            temp /= 10;
        }
    }

    int temp = num;
    while (temp > 0) {
        int remainder = temp % 10;
        sum += (int)pow(remainder, digits);
        temp /= 10;
    }

    if (sum == original) {
        return 1;
    }

    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    /* Possible weaknesses found:
     *  use of undeclared identifier 'INT_MIN'
     *  'INT_MIN' undeclared (first use in this function)
     *  use of undeclared identifier 'INT_MAX'
     *  each undeclared identifier is reported only once for each function it appears in
     *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
     *  'INT_MAX' undeclared (first use in this function)
     */
    if (*endptr != '\0' || val < INT_MIN || val > INT_MAX) {
        fprintf(stderr, "Invalid input: Not a valid integer\n");
        return EXIT_FAILURE;
    }

    int number = (int)val;

    if (is_armstrong(number)) {
        printf("%d is an Armstrong number.\n", number);
    } else {
        printf("%d is not an Armstrong number.\n", number);
    }

    return EXIT_SUCCESS;
}