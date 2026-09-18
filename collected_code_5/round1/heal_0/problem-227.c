#include <stdio.h>

int findMinimum(int a, int b, int c) {
    int min = a;
    if(b < min) {
        min = b;
    }
    if(c < min) {
        min = c;
    }
    return min;
}

int main() {
    int a, b, c;
    printf("Enter three numbers: ");
    scanf("%d %d %d", &a, &b, &c);
    int min = findMinimum(a, b, c);
    printf("Minimum number is: %d\n", min);
    return 0;
}