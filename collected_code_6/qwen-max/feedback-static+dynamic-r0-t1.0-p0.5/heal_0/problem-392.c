#include <stdio.h>
#include <stdlib.h>

int f(int n) {
    if (n < 12) return n;
    int a = f(n / 2);
    int b = f(n / 3);
    int c = f(n / 4);
    int d = f(n / 5);
    return (a + b + c + d > n) ? (a + b + c + d) : n;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("Maximum sum: %d\n", f(n));
    return 0;
}