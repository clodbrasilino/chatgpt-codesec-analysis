#include <stdio.h>

int square_perimeter(int side) {
    return 4 * side;
}

int main(void) {
    int side = 5;
    int perimeter = square_perimeter(side);
    printf("Perimeter of square with side %d is %d\n", side, perimeter);
    return 0;
}