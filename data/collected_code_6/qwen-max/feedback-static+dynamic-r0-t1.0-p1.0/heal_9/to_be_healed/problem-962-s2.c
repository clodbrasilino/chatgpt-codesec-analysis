#include <stdio.h>
#include <limits.h>
#include <stdint.h>

long long sum_of_evens(int l, int r) {
    long long sum = 0;
    if (l > r) {
        return sum;
    }
    if (l % 2 != 0) {
        l++;
    }
    for (int i = l; i <= r; i += 2) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223372036854775807 - -2 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000002,time:5524,execs:2270,op:havoc,rep:6)
         * UBSan: signed integer overflow: 9223372036854775807 - -22 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:5494,execs:2241,op:havoc,rep:16)
         */
        if (sum > LLONG_MAX - (long long)i) {
            return 0;
        }
        sum += i;
    }
    return sum;
}

int main() {
    int l, r;
    printf("Enter the range (l and r): ");
    if (scanf("%d %d", &l, &r) != 2) {
        printf("Invalid input\n");
        return 1;
    }
    if (l > INT_MAX || r > INT_MAX || l < INT_MIN || r < INT_MIN) {
        printf("Input out of range\n");
        return 1;
    }
    long long result = sum_of_evens(l, r);
    if (result == 0 && l <= r) {
        printf("Sum overflowed\n");
    } else {
        printf("Sum of even numbers between %d and %d is: %lld\n", l, r, result);
    }
    return 0;
}