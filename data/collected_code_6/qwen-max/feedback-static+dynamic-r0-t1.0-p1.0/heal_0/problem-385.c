#include <stdio.h>

int perrin_number(int n) {
    if (n == 0) return 3;
    if (n == 1) return 0;
    if (n == 2) return 2;
    return perrin_number(n-2) + perrin_number(n-3);
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    printf("The %dth Perrin number is: %d\n", n, perrin_number(n));
    return 0;
}