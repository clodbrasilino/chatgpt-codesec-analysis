#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected False, got <no output>
  *  test case 1 failed: expected True, got <no output>
  *  test case 2 failed: expected True, got <no output>
  */

int is_valid_triangle(long a, long b, long c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return 0;
    }
    if (a + b <= c) {
        return 0;
    }
    if (b + c <= a) {
        return 0;
    }
    if (a + c <= b) {
        return 0;
    }
    return 1;
}

int main(void) {
    long a, b, c;
    if (scanf("%ld %ld %ld", &a, &b, &c) != 3) {
        return EXIT_FAILURE;
    }
    if (is_valid_triangle(a, b, c)) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    return EXIT_SUCCESS;
}