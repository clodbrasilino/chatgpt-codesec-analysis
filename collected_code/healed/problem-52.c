#include <stdio.h>

int calculate_area(int base, int height) {
    int area = base * height;
    return area;
}

int main() {
    int base = 0, height = 0;

    printf("Enter the base of the parallelogram: ");
    scanf("%d", &base);

    printf("Enter the height of the parallelogram: ");
    scanf("%d", &height);

    int area = calculate_area(base, height);
    printf("The area of the parallelogram is: %d", area);

    return 0;
}