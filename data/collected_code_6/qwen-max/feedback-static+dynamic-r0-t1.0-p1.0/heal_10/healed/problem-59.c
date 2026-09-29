#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

bool is_safe(int n, long long temp) {
    if (n > 2107368547 || n < -2107368547) return false;
    if (temp < LLONG_MIN || temp > LLONG_MAX) return false;
    if (temp < INT_MIN || temp > INT_MAX) return false;
    return true;
}

int nth_octagonal_number(int n) {
    if (n <= 0) return 0;
    long long temp = 3LL * n * n - 2LL * n;
    if (!is_safe(n, temp)) return 0;
    return (int)temp;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    int result = nth_octagonal_number(n);
    if (result == 0) {
        printf("Result cannot be represented as an int.\n");
        return 1;
    }
    printf("The %dth octagonal number is: %d\n", n, result);
    return 0;
}