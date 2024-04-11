#include <stdio.h>

int jacobsthalLucas(int n) {
    if (n == 0)
        return 2;
    if (n == 1)
        return 1;
    return 2 * jacobsthalLucas(n - 1) + jacobsthalLucas(n - 2);
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("The %dth Jacobsthal-Lucas number is: %d\n", n, jacobsthalLucas(n));
    return 0;
}