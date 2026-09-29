#include <stdio.h>

int jacobsthal_lucas(int n) {
    if (n == 0)
        return 2;
    else if (n == 1)
        return 1;
    else
        return jacobsthal_lucas(n - 1) + 2 * jacobsthal_lucas(n - 2);
}

int main() {
    int n = 0;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    printf("The %dth Jacobsthal-Lucas number is: %d\n", n, jacobsthal_lucas(n));
    return 0;
}