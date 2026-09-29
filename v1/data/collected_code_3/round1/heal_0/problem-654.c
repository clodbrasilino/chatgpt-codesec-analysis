#include <stdio.h>

int rectanglePerimeter(int length, int width) {
    return 2 * (length + width);
}

int main() {
    int length, width;
    printf("Enter length of the rectangle: ");
    scanf("%d", &length);
    printf("Enter width of the rectangle: ");
    scanf("%d", &width);
    printf("Perimeter of the rectangle is: %d\n", rectanglePerimeter(length, width));
    return 0;
}