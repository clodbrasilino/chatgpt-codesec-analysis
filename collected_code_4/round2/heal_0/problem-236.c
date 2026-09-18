#include<stdio.h>
#include<math.h>

long long equilateral_triangles(int n) {
    if(n < 1) {
        return 0;
    }
    
    return (n * (n+1) * (2*n+1)) / 6;
}

int main() {
    int sideLength;
    long long triangleCount;
    
    printf("Enter the side length of the equilateral triangle: ");
    scanf("%d", &sideLength);
    
    triangleCount = equilateral_triangles(sideLength);

    printf("Maximum number of equilateral triangles that can be formed: %lld\n", triangleCount);
    
    return 0;
}