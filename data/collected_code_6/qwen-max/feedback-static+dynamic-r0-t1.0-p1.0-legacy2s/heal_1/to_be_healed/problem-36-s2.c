#include <stdio.h>
#include <stdlib.h>

int nth_digit(int a, int b, int n) {
    if (b <= 0 || n < 0) return -1;
    long long result = 0, remainder = a % b, multiplier = 1;
    for (int i = 0; i < n && remainder; ++i) {
        remainder *= 10;
        int digit = remainder / b;
        remainder %= b;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: -5349829096719403773 + -3890459611768029184 cannot be represented in type 'long long'
         * UBSan: signed integer overflow: 3 * -8446744073709551616 cannot be represented in type 'long long'
         */
        result += digit * multiplier;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 1000000000000000000 * 10 cannot be represented in type 'long long'
         */
        multiplier *= 10;
    }
    return remainder == 0 ? -1 : result;
}

int main() {
    int a, b, n;
    scanf("%d %d %d", &a, &b, &n);
    int digit = nth_digit(a, b, n);
    printf("%d\n", digit);
    return 0;
}