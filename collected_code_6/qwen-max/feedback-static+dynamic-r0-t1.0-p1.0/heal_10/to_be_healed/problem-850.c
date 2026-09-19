#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  'LONG_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

bool canFormTriangle(long a, long b, long c) {
    if (a <= 0 || b <= 0 || c <= 0) return false;
    /* Possible weaknesses found:
     *  'LONG_MAX' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     *  use of undeclared identifier 'LONG_MAX'
     */
    if (a > LONG_MAX - b || a > b + c) return false;
    /* Possible weaknesses found:
     *  use of undeclared identifier 'LONG_MAX'
     */
    if (b > LONG_MAX - a || b > a + c) return false;
    /* Possible weaknesses found:
     *  use of undeclared identifier 'LONG_MAX'
     */
    if (c > LONG_MAX - a || c > a + b) return false;
    return true;
}

int main() {
    long side1, side2, side3;
    printf("Enter three sides of a triangle: ");
    scanf("%ld %ld %ld", &side1, &side2, &side3);

    if (canFormTriangle(side1, side2, side3)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}