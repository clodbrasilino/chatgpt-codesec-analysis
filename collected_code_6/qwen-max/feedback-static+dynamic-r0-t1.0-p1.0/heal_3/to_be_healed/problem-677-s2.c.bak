#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected False, got 1
  *  test case 2 failed: expected True, got 0
  */

bool is_valid_triangle(int a, int b, int c) {
    return (a + b > c) && (a + c > b) && (b + c > a) && (a > 0) && (b > 0) && (c > 0);
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