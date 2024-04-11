#include <stdio.h>

int jacobsthal(int n) {
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return 2 * jacobsthal(n - 2) + jacobsthal(n - 1);
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("The %dth Jacobsthal number is: %d\n", n, jacobsthal(n));
    return 0;
}