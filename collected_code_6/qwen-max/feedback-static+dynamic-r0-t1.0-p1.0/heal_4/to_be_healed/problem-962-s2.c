#include <stdio.h>
#include <limits.h>

long sum_of_evens(int l, int r) {
    long sum = 0;
    if (l > r) {
        return sum;
    }
    if (l % 2 != 0) {
        l++;
    }
    for (int i = l; i <= r; i += 2) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223372036854775807 - -1961634962 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000002,time:59471,execs:16588,op:havoc,rep:3)
         * UBSan: signed integer overflow: 9223372036854775807 - -2072745074 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:4236,execs:1313,op:havoc,rep:8)
         */
        if (sum > LONG_MAX - i) {
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
    long result = sum_of_evens(l, r);
    printf("Sum of even numbers between %d and %d is: %ld\n", l, r, result);
    return 0;
}