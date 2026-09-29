#include <stdio.h>

int countRectangles(int r) {
    int count = 0;
    
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= r; j++) {
            if ((i * i) + (j * j) <= (r * r)) {
                count++;
            }
        }
    }
    
    return count;
}

int main() {
    int radius = 0;
    printf("Enter radius of the circle: ");
    scanf("%d", &radius);
    
    int rectangleCount = countRectangles(radius);
    printf("Number of rectangles in circle: %d\n", rectangleCount);
    
    return 0;
}