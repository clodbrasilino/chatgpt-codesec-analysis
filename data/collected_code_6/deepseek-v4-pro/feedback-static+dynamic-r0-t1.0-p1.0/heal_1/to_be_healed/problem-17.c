#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 40, got <no output>
  *  test case 1 failed: expected 20, got <no output>
  *  test case 2 failed: expected 16, got <no output>
  */

int square_perimeter(int side) {
    return 4 * side;
}

int main(void) {
    int side = 5;
    int perimeter = square_perimeter(side);
    printf("Perimeter of square with side %d is %d\n", side, perimeter);
    return 0;
}