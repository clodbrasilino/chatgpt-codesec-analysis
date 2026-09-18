#include<stdio.h>

int calculatePerimeter(int length, int width) {
    if(length <= 0 || width <= 0) {
        printf("Invalid input. Rectangle dimensions should be positive integers.\n");
        return -1;
    }
    int perimeter = 2 * (length + width);
    return perimeter;
}

int main() {
    int length = 0, width = 0;
    printf("Enter length of the rectangle: ");
    scanf("%d", &length);

    printf("Enter width of the rectangle: ");
    scanf("%d", &width);

    int perimeter = calculatePerimeter(length, width);

    if(perimeter != -1) {
        printf("The perimeter of the rectangle is: %d\n", perimeter);
    }
    return 0;
}