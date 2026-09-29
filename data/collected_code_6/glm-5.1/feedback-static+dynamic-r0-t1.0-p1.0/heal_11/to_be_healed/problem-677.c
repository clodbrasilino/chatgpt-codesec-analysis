#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected True, got 0
  *  test case 0 failed: expected False, got 1
  */

int is_valid_triangle(long a, long b, long c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return 0;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 30 + 9223372036854775807 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000003,time:855,execs:871,op:havoc,rep:1)
     */
    if (a + b > c && a + c > b && b + c > a) {
        return 1;
    }
    return 0;
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