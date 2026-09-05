#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'LLONG_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

int count_digits(long long n) {
    if (n == 0) {
        return 1;
    }
    /* Possible weaknesses found:
     *  use of undeclared identifier 'LLONG_MIN'
     *  'LLONG_MIN' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     */
    if (n == LLONG_MIN) {
        return 19;
    }
    if (n < 0) {
        n = -n;
    }
    int count = 0;
    while (n > 0) {
        count++;
        n /= 10;
    }
    return count;
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
    long long num = strtoll(argv[1], &endptr, 10);
    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    int digits = count_digits(num);
    printf("%d\n", digits);
    return EXIT_SUCCESS;
}