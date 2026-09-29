#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 /* Possible weaknesses found:
  *  'LLONG_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

int count_digits(long long n) {
    if (n == 0) {
        return 1;
    }
    
    if (n < 0) {
        /* Possible weaknesses found:
         *  use of undeclared identifier 'LLONG_MIN'
         *  each undeclared identifier is reported only once for each function it appears in
         *  'LLONG_MIN' undeclared (first use in this function)
         */
        if (n == LLONG_MIN) {
            /* Possible weaknesses found:
             *  'LLONG_MAX' undeclared (first use in this function)
             *  use of undeclared identifier 'LLONG_MAX'
             *  'LLONG_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
             */
            n = LLONG_MAX;
        } else {
            n = -n;
        }
    }
    
    int count = 0;
    while (n > 0) {
        count++;
        n /= 10;
    }
    
    return count;
}

int have_same_number_of_digits(long long a, long long b) {
    return count_digits(a) == count_digits(b);
}

int main(void) {
    long long num1 = 0;
    long long num2 = 0;
    
    if (scanf("%lld %lld", &num1, &num2) != 2) {
        return EXIT_FAILURE;
    }
    
    if (have_same_number_of_digits(num1, num2)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    
    return EXIT_SUCCESS;
}