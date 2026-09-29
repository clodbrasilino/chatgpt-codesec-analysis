#include <stdio.h>

char *determine_triangle_type(int a, int b, int c) {
    if (a <= 0 || b <= 0 || c <= 0) return "Invalid";
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 1111111111 + 1199545584 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:12695,execs:5188,op:havoc,rep:9)
     * UBSan: signed integer overflow: 1139355592 + 1199545584 cannot be represented in type 'int'
     */
    if (a + b <= c || a + c <= b || b + c <= a) return "Invalid";

    if (a == b && b == c) return "Equilateral";
    if (a == b || a == c || b == c) return "Isosceles";
    return "Scalene";
}

int main() {
    int side1, side2, side3;
    char *result;

    printf("Enter the sides of the triangle: ");
    scanf("%d %d %d", &side1, &side2, &side3);

    result = determine_triangle_type(side1, side2, side3);
    printf("The triangle is: %s\n", result);

    return 0;
}