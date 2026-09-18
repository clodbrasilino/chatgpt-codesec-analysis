#include <stdio.h>
#include <limits.h>

int findLargestK(int x, int y) {
    if (y < x && y >= 0 && x > 0) {
        return INT_MAX - (INT_MAX % x) + y;
    }
    return -1;
}

int main() {
    int x, y;
    printf("Enter x: ");
    scanf("%d", &x);
    printf("Enter y: ");
    scanf("%d", &y);
    int result = findLargestK(x, y);
    if(result != -1) {
        printf("The largest value of k is: %d\n", result);
    } else {
        printf("Invalid values of x and y\n");
    }
    return 0;
}