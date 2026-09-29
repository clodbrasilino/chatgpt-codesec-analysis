#include <stdio.h>

int calculate_perimeter(int length, int width) {
    return 2 * (length + width);
}

int main() {
    int length = 5;
    int width = 3;
    int perimeter = calculate_perimeter(length, width);
    printf("Perimeter of the rectangle: %d\n", perimeter);
    return 0;
}