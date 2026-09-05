#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

int find_difference(int num) {
    int even_sum = 0;
    int odd_sum = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'digit' can be reduced. [variableScope]
     */
    int digit;
    long long n = num;

    if (n < 0) {
        n = -n;
    }

    if (n == 0) {
        return 0;
    }

    while (n > 0) {
        digit = n % 10;
        if (digit % 2 == 0) {
            even_sum += digit;
        } else {
            odd_sum += digit;
        }
        n /= 10;
    }

    return even_sum - odd_sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int number;
    int result;

    if (argc != 2) {
        if (fprintf(stderr, "Usage: %s <integer>\n", argv[0]) < 0) {
            return EXIT_FAILURE;
        }
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
    if (endptr == argv[1] || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
        if (fprintf(stderr, "Invalid input. Please provide a valid integer.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    number = (int)val;
    result = find_difference(number);

    if (printf("Difference: %d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}