#include <stdio.h>
 
int countMaxEquilateralTriangles(int length) {
    if (length < 1)
        return 0;
        
    int maxTriangles = 0;
    int i;
 
    for (i = 1; i <= length; i++) {
        if (length % i == 0 && i % 2 == 0) {
            maxTriangles++;
        }
    }
 
    return maxTriangles;
}
 
int main() {
    int triangleLength = 6;
    int maxTriangles = countMaxEquilateralTriangles(triangleLength);
 
    printf("The maximum number of equilateral triangles that can be formed is %d.", maxTriangles);
 
    return 0;
}