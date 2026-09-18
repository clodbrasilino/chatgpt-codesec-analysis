#include <stdio.h>

int calculate_perimeter(int side) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 4 * -1037027101 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000002,time:451,execs:232,op:havoc,rep:1)
     */
    return 4 * side;
}

int main() {
    int side;
    printf("Enter the side of the square: ");
    if (scanf("%d", &side) == 1) {
        int perimeter = calculate_perimeter(side);
        printf("The perimeter of the square is: %d\n", perimeter);
    } else {
        printf("Invalid input.\n");
    }
    return 0;
}