#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

int calculate_sum(int n) {
    if (n <= 0) {
        return 0;
    }
    int sum = 0;
    int current = n;
    while (current > 0) {
        sum += current;
        current -= 2;
    }
    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    /* Possible weaknesses found:
     *  use of undeclared identifier 'INT_MAX'
     *  'INT_MAX' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     */
    if (*endptr != '\0' || val < 0 || val > INT_MAX) {
        fprintf(stderr, "Invalid input: must be a non-negative integer within range\n");
        return EXIT_FAILURE;
    }
    int n = (int)val;
    int result = calculate_sum(n);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}