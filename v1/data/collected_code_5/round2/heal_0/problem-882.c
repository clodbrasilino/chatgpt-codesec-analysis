#include <stdio.h>

int perimeterOfParallelogram(int base, int side) {
    if (base <= 0 || side <= 0) {
        return -1;
    }
    return 2 * (base + side);
}

int main() {
    int base, side, perimeter;

    printf("Enter base and side of the parallelogram: ");
    scanf("%d%d", &base, &side);
    
    perimeter = perimeterOfParallelogram(base, side);
    
    if (perimeter < 0) {
        printf("Base or side length of a parallelogram can not be less than or equal to zero.\n");
        return -1;
    }

    printf("Perimeter of the parallelogram is %d\n", perimeter);

    return 0;
}