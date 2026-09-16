#include <stdio.h>
#include <stdlib.h>

int count_integral_coords(int x1, int y1, int x2, int y2) {
    if (x1 > x2 || y1 > y2) return 0;
    int width = x2 - x1 + 1;
    int height = y2 - y1 + 1;
    return width * height;
}

int main() {
    int x1, y1, x2, y2;
    printf("Enter the coordinates of the bottom-left corner (x1, y1): ");
    scanf("%d %d", &x1, &y1);
    printf("Enter the coordinates of the top-right corner (x2, y2): ");
    scanf("%d %d", &x2, &y2);

    int result = count_integral_coords(x1, y1, x2, y2);
    printf("Number of integral coordinates inside the square: %d\n", result);

    return 0;
}