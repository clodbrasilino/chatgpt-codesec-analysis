#include <stdio.h>

int findLargestK(int x, int y) {
    if(y < x) {
        return y + (x * (1000000 - 1));
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
        printf("The largest possible value of k such that k modulo x is y is: %d\n", result);
    } else {
        printf("No possible value of k found.\n");
    }
    return 0;
}