#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

long long sum_of_fourth_power_even(int n) {
    long long sum = 0;
    int64_t even;
    for (int i = 1; i <= n; ++i) {
        even = 2 * (int64_t)i;
        sum += even * even * even * even;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter the number of even natural numbers: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Invalid input.\n");
        return 1;
    }
    long long result = sum_of_fourth_power_even(n);
    printf("The sum of the fourth power of the first %d even natural numbers is: %lld\n", n, result);
    return 0;
}