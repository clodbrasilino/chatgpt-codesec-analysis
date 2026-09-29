#include <stdio.h>
#include <limits.h>

int sum_series(int n) {
    long long sum = 0;
    for (int i = n; i > 0; i -= 2) {
        if (LONG_MAX - i < sum) {
            printf("Overflow detected, cannot compute sum.\n");
            return -1;
        }
        sum += i;
    }
    return (int)sum;
}

int main() {
    int n;
    printf("Enter an integer: ");
    scanf("%d", &n);
    int result = sum_series(n);
    if (result != -1) {
        printf("The sum of the series is: %d\n", result);
    }
    return 0;
}