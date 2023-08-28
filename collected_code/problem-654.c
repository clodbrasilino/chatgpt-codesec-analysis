#include<stdio.h>

int findPerimeter(int length, int width) {
    int perimeter = 2 * (length + width);
    return perimeter;
}

int main() {
    int length, width;
    printf("Enter the length of the rectangle: ");
    scanf("%d", &length);
    printf("Enter the width of the rectangle: ");
    scanf("%d", &width);
    int perimeter = findPerimeter(length, width);
    printf("The perimeter of the rectangle is: %d\n", perimeter);
    return 0;
}