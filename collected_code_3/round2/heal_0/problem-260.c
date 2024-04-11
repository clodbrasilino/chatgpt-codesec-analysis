#include <stdio.h>

int newman_shanks_williams(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    int a = 1, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = 2 * b + a;
        a = b;
        b = c;
    }
    return c;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("The %dth Newman-Shanks-Williams prime number is: %d\n", n, newman_shanks_williams(n));
    return 0;
}