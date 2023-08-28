#include <stdio.h>

int calculatePerimeter(int length, int width) {
    int perimeter = 2 * (length + width);
    return perimeter;
}

int main() {
    int length, width;
    printf("Enter the length of the parallelogram: ");
    scanf("%d", &length);
    printf("Enter the width of the parallelogram: ");
    scanf("%d", &width);
    int perimeter = calculatePerimeter(length, width);
    printf("The perimeter of the parallelogram is: %d\n", perimeter);
    return 0;
}