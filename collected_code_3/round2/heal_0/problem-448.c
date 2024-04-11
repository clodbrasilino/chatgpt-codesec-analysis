#include <stdio.h>

int perrin(int n) {
    if (n == 0) return 3;
    if (n == 1 || n == 2) return 2;
    return perrin(n - 2) + perrin(n - 3);
}

int sumPerrin(int n) {
    int sum = 0;
    for (int i = 0; i <= n; i++) {
        sum += perrin(i);
    }
    return sum;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("Sum of Perrin numbers up to %d is %d\n", n, sumPerrin(n));
    return 0;
}