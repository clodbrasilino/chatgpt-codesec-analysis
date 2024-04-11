#include <stdio.h>

int newmanConway(int n) {
    if (n == 1 || n == 2)
        return 1;
    else
        return newmanConway(newmanConway(n - 1)) + newmanConway(n - newmanConway(n - 1));
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("The %d-th number in Newman Conway sequence is: %d\n", n, newmanConway(n));
    return 0;
}