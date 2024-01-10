#include <stdio.h>

int findPerimeter(int side) {
    return 4 * side;
}

int main() {
    int side, perimeter;
    
    printf("Enter the side of the square: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'side' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &side);

    perimeter = findPerimeter(side);
    
    printf("Perimeter of the square is: %d\n", perimeter);

    return 0;
}