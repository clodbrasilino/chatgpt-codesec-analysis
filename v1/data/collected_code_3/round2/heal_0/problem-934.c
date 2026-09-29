#include <stdio.h>

int delannoy(int n, int m) {
    if (n == 0 || m == 0)
        return 1;
    return delannoy(n-1, m) + delannoy(n-1, m-1) + delannoy(n, m-1);
}

int nthDelannoy(int n) {
    return delannoy(n, n);
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("The %dth Delannoy number is: %d\n", n, nthDelannoy(n));
    return 0;
}