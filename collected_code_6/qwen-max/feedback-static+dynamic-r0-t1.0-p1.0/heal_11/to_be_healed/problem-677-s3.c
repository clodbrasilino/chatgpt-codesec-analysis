#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected False, got 1
  *  test case 2 failed: expected True, got 0
  */

bool is_valid_triangle(int a, int b, int c) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 952207132 + 1933270813 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000006,time:48306,execs:23093,op:havoc,rep:2)
     */
    return a > 0 && b > 0 && c > 0 && (a + b > c) && (a + c > b) && (b + c > a);
}

int main() {
    int side1, side2, side3;
    
    printf("Enter three sides of the triangle: ");
    if (scanf("%d %d %d", &side1, &side2, &side3) != 3) {
        fprintf(stderr, "Invalid input\n");
        exit(EXIT_FAILURE);
    }

    if (is_valid_triangle(side1, side2, side3)) {
        printf("The triangle is valid.\n");
    } else {
        printf("The triangle is not valid.\n");
    }
    
    return 0;
}