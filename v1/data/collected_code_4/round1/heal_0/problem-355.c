#include<stdio.h>
#include<math.h>

int countRectangles(double radius) {
    if (radius <= 0) {
        return 0;
    }
    int side = radius * sqrt(2);
    int numRectangles = (side * (side + 1) * (2 * side + 1)) / 6;
    
    return numRectangles;
}

int main() {
    double radius;
    printf("Enter the radius.\n");
    scanf("%lf", &radius);
    int result = countRectangles(radius);
    
    if(result!=0) {
        printf("Number of rectangles in the circle: %d\n", result);
    } else {
        printf("Radius should be larger than 0.\n");
    }
    
    return 0;
}