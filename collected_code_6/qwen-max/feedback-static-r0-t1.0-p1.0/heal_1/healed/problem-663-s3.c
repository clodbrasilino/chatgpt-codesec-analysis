#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_largest_k(int x, int y) {
    if (x <= 0 || y < 0 || y >= x) {
        return -1;
    }
    return (y + (INT_MAX / x) * x);
}

int main() {
    int x, y;
    printf("Enter the value of x: ");
    scanf("%d", &x);
    printf("Enter the value of y: ");
    scanf("%d", &y);

    int result = find_largest_k(x, y);
    if (result == -1) {
        printf("Invalid input.\n");
    } else {
        printf("The largest possible value of k is: %d\n", result);
    }

    return 0;
}