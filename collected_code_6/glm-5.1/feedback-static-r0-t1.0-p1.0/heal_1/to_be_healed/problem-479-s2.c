#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

int find_first_digit(int number) {
    if (number == 0) {
        return 0;
    }
    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  use of undeclared identifier 'INT_MIN'
     *  'INT_MIN' undeclared (first use in this function)
     */
    if (number == INT_MIN) {
        return 2;
    }
    int n = abs(number);
    while (n >= 10) {
        n /= 10;
    }
    return n;
}

int main(void) {
    int num;
    if (scanf("%d", &num) != 1) {
        return EXIT_FAILURE;
    }
    int result = find_first_digit(num);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}