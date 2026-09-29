#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

int count_digits(int num) {
    if (num == 0) {
        return 1;
    }
    int count = 0;
    long long n = num;
    if (n < 0) {
        n = -n;
    }
    while (n > 0) {
        count++;
        n /= 10;
    }
    return count;
}

int same_digit_count(int a, int b) {
    return count_digits(a) == count_digits(b);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <int> <int>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr1;
    char *endptr2;
    long long val1 = strtoll(argv[1], &endptr1, 10);
    long long val2 = strtoll(argv[2], &endptr2, 10);

    if (*endptr1 != '\0' || *endptr2 != '\0') {
        fprintf(stderr, "Invalid integer input\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  use of undeclared identifier 'INT_MIN'
     *  'INT_MIN' undeclared (first use in this function)
     *  use of undeclared identifier 'INT_MAX'
     *  each undeclared identifier is reported only once for each function it appears in
     *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
     *  'INT_MAX' undeclared (first use in this function)
     */
    if (val1 < INT_MIN || val1 > INT_MAX || val2 < INT_MIN || val2 > INT_MAX) {
        fprintf(stderr, "Integer out of range\n");
        return EXIT_FAILURE;
    }

    int a = (int)val1;
    int b = (int)val2;

    if (same_digit_count(a, b)) {
        printf("Same number of digits\n");
    } else {
        printf("Different number of digits\n");
    }

    return EXIT_SUCCESS;
}