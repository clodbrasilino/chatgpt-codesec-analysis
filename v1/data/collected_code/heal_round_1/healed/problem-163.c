#include <stdio.h>
#include <math.h>

float calculateAreaOfRegularPolygon(int numSides, float sideLength) {
    float area;
    area = (numSides * sideLength * sideLength) / (4 * tan(M_PI / numSides));
    return area;
}

int main() {
    int numSides = 0;
    float sideLength = 0.0;

    printf("Enter the number of sides of the regular polygon: ");
    scanf("%d", &numSides);
    
    printf("Enter the length of each side of the regular polygon: ");
    scanf("%f", &sideLength);

    printf("The area of the regular polygon is: %.2f\n", calculateAreaOfRegularPolygon(numSides, sideLength));
    return 0;
}