#include <stdio.h>
#include <limits.h>

int average_of_odd_numbers(int n) {
    if (n < 1 || n % 2 == 0) {
        return -1;
    }

    long long sum = 0;
    int count = 0;

    for (int i = 1; i <= n; i += 2) {
        if (sum > LLONG_MAX - i) {
            return -1;
        }
        sum += i;
        count++;
    }

    return (int)(sum / count);
}

int main(void) {
    int n;
    int result;

    printf("Enter an odd number: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    result = average_of_odd_numbers(n);
    if (result == -1) {
        printf("Input must be a positive odd number or overflow occurred.\n");
        return 1;
    }

    printf("Average of odd numbers up to %d is %d\n", n, result);
    return 0;
}