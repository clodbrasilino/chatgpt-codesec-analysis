#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

int add_and_check(int a, int b, int low, int high) {
    long long sum = (long long)a + (long long)b;
    /* Possible weaknesses found:
     *  use of undeclared identifier 'INT_MIN'
     *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
     *  'INT_MIN' undeclared (first use in this function)
     *  use of undeclared identifier 'INT_MAX'
     *  each undeclared identifier is reported only once for each function it appears in
     *  'INT_MAX' undeclared (first use in this function)
     */
    if (sum > INT_MAX || sum < INT_MIN) {
        return -1;
    }
    int int_sum = (int)sum;
    if (int_sum >= low && int_sum <= high) {
        return 20;
    }
    return int_sum;
}

int main(void) {
    int a = 5;
    int b = 10;
    int low = 10;
    int high = 20;
    int result = add_and_check(a, b, low, high);
    printf("%d\n", result);
    return 0;
}