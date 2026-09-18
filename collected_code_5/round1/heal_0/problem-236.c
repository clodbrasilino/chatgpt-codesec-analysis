#include <stdio.h>

long long findTriangles(long long n) {
    if(n < 0) {
        printf("Input can't be negative.\n");
        return -1;
    }

    long long sum = 0;

    while(n > 0) {
        sum = sum + (n * (n+1) / 2);
        n--;
    }
    return sum;
}

int main() {
    long long n;
    printf("Enter the side length of the equilateral triangle: ");
    scanf("%lld", &n);
    long long result = findTriangles(n);
    if(result != -1) {
        printf("Maximum number of triangles: %lld\n", result);
    }

    return 0;
}