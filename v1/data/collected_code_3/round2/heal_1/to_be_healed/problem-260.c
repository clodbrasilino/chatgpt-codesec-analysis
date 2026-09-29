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
    /* Possible weaknesses found:
     *  use of uninitialized value 'c' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
     */
    return c;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("The %dth Newman-Shanks-Williams prime number is: %d\n", n, newman_shanks_williams(n));
    return 0;
}