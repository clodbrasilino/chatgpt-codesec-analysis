#include <stdio.h>

int pellNumber(int n) {
    if (n <= 0)
        return 0;
    else if (n == 1)
        return 1;
    else {
        int a = 0, b = 1, c;
        for (int i = 2; i <= n; i++) {
            c = 2 * b + a;
            a = b;
            b = c;
        }
        return b;
    }
}

int main() {
    int n = 0;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    if (n < 0) {
        printf("Invalid input. Please enter non-negative number.\n");
        return -1;
    }
    int nthPell = pellNumber(n);
    printf("The %dth Pell number is %d\n", n, nthPell);
    return 0;
}