#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected True, got 0
  *  test case 0 failed: expected False, got 1
  */

bool is_valid_triangle(int a, int b, int c) {
    if (a <= 0 || b <= 0 || c <= 0) return false;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 2093175460 + 2076732068 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:602,execs:600,op:havoc,rep:9)
     * UBSan: signed integer overflow: 1658710016 + 1316134912 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000005,time:37089,execs:32216,op:havoc,rep:6)
     */
    if (a + b > c && a + c > b && b + c > a) return true;
    return false;
}

int main() {
    int side1, side2, side3;
    bool valid;

    printf("Enter the three sides of the triangle: ");
    if (scanf("%d %d %d", &side1, &side2, &side3) != 3) {
        printf("Invalid input.\n");
        return 1;
    }

    valid = is_valid_triangle(side1, side2, side3);

    if (valid) {
        printf("The triangle is valid.\n");
    } else {
        printf("The triangle is not valid.\n");
    }

    return 0;
}