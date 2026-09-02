#include <stdio.h>
#include <stdlib.h>

int count_integral_coordinates(int x1, int y1, int x2, int y2) {
    if (x1 > x2) return 0;
    if (y1 > y2) return 0;
    return (x2 - x1 + 1) * (y2 - y1 + 1);
}

int main() {
    int x1 = 0, y1 = 0, x2 = 5, y2 = 5;
    int result = count_integral_coordinates(x1, y1, x2, y2);
    printf("Number of integral coordinates: %d\n", result);
    return 0;
}