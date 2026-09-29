#include <stdio.h>

int countRectangles(int r) {
    int count = 0;
    
    // Loop for each possible rectangle
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= r; j++) {
            // Check if rectangle fits within the circle
            if ((i * i) + (j * j) <= (r * r)) {
                count++;
            }
        }
    }
    
    return count;
}

int main() {
    int radius;
    printf("Enter radius of the circle: ");
    scanf("%d", &radius);
    
    int rectangleCount = countRectangles(radius);
    printf("Number of rectangles in circle: %d\n", rectangleCount);
    
    return 0;
}