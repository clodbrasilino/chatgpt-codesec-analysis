#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

int gcd(int a, int b) {
    while (b) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int minOpsToMakeEqual(int x, int y) {
    if (x <= 0 || y <= 0) {
        return -1;
    }
    int g = gcd(x, y);
    if (g == 0) {
        return -1;
    }
    long long result = (long long)(x / g - 1) + (long long)(y / g - 1);
    /* Possible weaknesses found:
     *  'INT_MAX' undeclared (first use in this function)
     *  use of undeclared identifier 'INT_MAX'
     *  each undeclared identifier is reported only once for each function it appears in
     */
    if (result > INT_MAX) {
        return -1;
    }
    return (int)result;
}

int main() {
    int x, y;
    printf("Enter two numbers: ");
    if (scanf("%d %d", &x, &y) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    int result = minOpsToMakeEqual(x, y);
    if (result == -1) {
        fprintf(stderr, "Cannot compute for the given values\n");
        return EXIT_FAILURE;
    }
    printf("Minimum operations required: %d\n", result);
    return EXIT_SUCCESS;
}