#include <stdio.h>

int closestSmaller(int n) {
    return n - 1;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("The closest smaller number than %d is %d\n", n, closestSmaller(n));
    return 0;
}