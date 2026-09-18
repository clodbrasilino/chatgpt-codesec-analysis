#include <stdio.h>
#include <stdbool.h>

bool is_valid_triangle(int a, int b, int c) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 215014507 + 2007974001 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000003,time:962,execs:392,op:havoc,rep:2)
     */
    return a > 0 && b > 0 && c > 0 && (a + b > c) && (a + c > b) && (b + c > a);
}

int main() {
    int side1, side2, side3;
    printf("Enter the three sides of the triangle: ");
    if (scanf("%d %d %d", &side1, &side2, &side3) != 3) {
        printf("Invalid input.\n");
        return 1;
    }
    if (is_valid_triangle(side1, side2, side3)) {
        printf("The triangle is valid.\n");
    } else {
        printf("The triangle is not valid.\n");
    }
    return 0;
}