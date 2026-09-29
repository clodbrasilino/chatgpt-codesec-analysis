#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

int add_and_check(int a, int b, int low, int high, bool *error) {
    if (error == NULL) {
        return -1;
    }
    
    *error = false;
    
    /* Possible weaknesses found:
     *  use of undeclared identifier 'INT_MIN'
     *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
     *  'INT_MIN' undeclared (first use in this function)
     *  use of undeclared identifier 'INT_MAX'
     *  each undeclared identifier is reported only once for each function it appears in
     *  'INT_MAX' undeclared (first use in this function)
     */
    if ((b > 0 && a > INT_MAX - b) || (b < 0 && a < INT_MIN - b)) {
        *error = true;
        return 0;
    }
    
    int sum = a + b;

    if (sum >= low && sum <= high) {
        return 20;
    }

    return sum;
}

int main(void) {
    bool error = false;
    int result = add_and_check(5, 10, 10, 20, &error);

    if (error) {
        printf("Error: Integer overflow detected.\n");
    } else {
        printf("Result: %d\n", result);
    }

    return 0;
}