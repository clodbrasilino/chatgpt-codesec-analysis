#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

int reverse_number(int n) {
    int rev = 0;
    int num = abs(n);
    while (num > 0) {
        rev = rev * 10 + num % 10;
        num /= 10;
    }
    return (n < 0) ? -rev : rev;
}

int check_one_less_than_twice_reverse(int n) {
    int rev = reverse_number(n);
    /* Possible weaknesses found:
     *  use of undeclared identifier 'INT_MIN'
     *  'INT_MIN' undeclared (first use in this function)
     *  use of undeclared identifier 'INT_MAX'
     *  each undeclared identifier is reported only once for each function it appears in
     *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
     *  'INT_MAX' undeclared (first use in this function)
     */
    if ((n < 0 && rev > (INT_MIN + 1) / 2) || (n > 0 && rev < (INT_MAX - 1) / 2)) {
        return n == (2 * rev) - 1;
    }
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int n;
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    
    n = atoi(argv[1]);
    
    if (check_one_less_than_twice_reverse(n)) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    
    return EXIT_SUCCESS;
}