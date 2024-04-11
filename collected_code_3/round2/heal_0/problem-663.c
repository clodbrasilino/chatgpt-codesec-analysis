#include <stdio.h>

int findMaxK(int x, int y) {
    if(y < x) {
        return (x - 1) + y;
    } else {
        return -1;
    }
}

int main() {
    int x, y;
    printf("Enter x: ");
    scanf("%d", &x);
    printf("Enter y: ");
    scanf("%d", &y);
    int result = findMaxK(x, y);
    if(result != -1) {
        printf("The largest possible value of k such that k modulo x is y is: %d\n", result);
    } else {
        printf("No possible value of k exists.\n");
    }
    return 0;
}