#include <stdio.h>

int pellNumber(int n) {
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        return 2 * pellNumber(n - 1) + pellNumber(n - 2);
    }
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("The %dth Pell number is: %d\n", n, pellNumber(n));
    return 0;
}