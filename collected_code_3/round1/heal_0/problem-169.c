#include <stdio.h>

long long int pellNumber(int n) {
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        long long int x = 0, y = 1, z;
        for (int i = 2; i <= n; i++) {
            z = 2 * y + x;
            x = y;
            y = z;
        }
        return y;
    }
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("The %dth Pell number is %lld\n", n, pellNumber(n));
    return 0;
}