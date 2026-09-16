#include <stdio.h>

int square_perimeter(int side) {
    return 4 * side;
}

int main(void) {
    int side = 10;
    int perimeter = square_perimeter(side);
    printf("%d\n", perimeter);
    return 0;
}