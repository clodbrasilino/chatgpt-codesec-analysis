#include <stdio.h>
#include <stdlib.h>

int f(int n) {
    if (n <= 1) return n;
    int a = f(n / 2);
    int b = f(n / 3);
    int c = f(n / 4);
    int d = f(n / 5);
    return (a + b + c + d) > n ? (a + b + c + d) : n;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    int result = f(n);
    printf("The maximum sum is: %d\n", result);
    return 0;
}