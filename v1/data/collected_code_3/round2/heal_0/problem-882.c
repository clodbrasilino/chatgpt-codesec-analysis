#include <stdio.h>

int perimeter(int base, int side) {
    return 2 * (base + side);
}

int main() {
    int base, side;
    printf("Enter base: ");
    scanf("%d", &base);
    printf("Enter side: ");
    scanf("%d", &side);
    printf("Perimeter of the parallelogram: %d\n", perimeter(base, side));
    return 0;
}