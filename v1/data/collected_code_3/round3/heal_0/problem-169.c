#include <stdio.h>

long long int pell_number(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    long long int x = 0, y = 1, z;
    for (int i = 2; i <= n; i++) {
        z = 2 * y + x;
        x = y;
        y = z;
    }
    return y;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("The %dth Pell number is %lld\n", n, pell_number(n));
    return 0;
}