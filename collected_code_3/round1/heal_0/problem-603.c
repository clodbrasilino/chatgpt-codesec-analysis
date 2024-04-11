#include <stdio.h>

int lucid(int n) {
    int a = 2, b = 1, c;
    if (n == 1) return 1;
    if (n == 2) return 2;
    while (1) {
        c = a + b;
        if (c > n) return a;
        b = a;
        a = c;
    }
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("The largest lucid number less than or equal to %d is %d\n", n, lucid(n));
    return 0;
}