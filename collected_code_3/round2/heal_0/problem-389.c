#include <stdio.h>

int lucasNumber(int n) {
    if (n == 0)
        return 2;
    if (n == 1)
        return 1;

    int a = 2, b = 1, c, i;

    for (i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("The %d'th Lucas number is %d\n", n, lucasNumber(n));
    return 0;
}