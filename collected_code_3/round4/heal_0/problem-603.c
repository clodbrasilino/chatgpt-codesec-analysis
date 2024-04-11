#include <stdio.h>

int lucid(int n) {
    int a = 2, b = 1, c = 3;
    while (c <= n) {
        a = b;
        b = c;
        c = a + b;
    }
    return b;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("The largest lucid number less than or equal to %d is %d\n", n, lucid(n));
    return 0;
}