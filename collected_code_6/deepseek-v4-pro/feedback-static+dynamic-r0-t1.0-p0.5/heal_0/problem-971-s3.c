#include <stdio.h>
#include <limits.h>

int maxSegments(int n, int a, int b, int c) {
    if (n < 0) return INT_MIN;
    if (n == 0) return 0;
    
    int maxA = maxSegments(n - a, a, b, c);
    int maxB = maxSegments(n - b, a, b, c);
    int maxC = maxSegments(n - c, a, b, c);
    
    int max = maxA;
    if (maxB > max) max = maxB;
    if (maxC > max) max = maxC;
    
    if (max == INT_MIN) return INT_MIN;
    return max + 1;
}

int main(void) {
    int n, a, b, c;
    
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    printf("Enter a, b, c: ");
    if (scanf("%d %d %d", &a, &b, &c) != 3) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (a <= 0 || b <= 0 || c <= 0) {
        printf("Segment lengths must be positive\n");
        return 1;
    }
    
    int result = maxSegments(n, a, b, c);
    
    if (result == INT_MIN) {
        printf("Cannot form segments\n");
    } else {
        printf("Maximum segments: %d\n", result);
    }
    
    return 0;
}