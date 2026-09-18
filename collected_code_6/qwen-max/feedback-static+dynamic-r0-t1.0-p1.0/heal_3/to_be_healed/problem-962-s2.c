#include <stdio.h>
#include <limits.h>

int sum_of_evens(int l, int r) {
    long sum = 0;
    if (l > r) {
        return (int)sum;
    }
    if (l % 2 != 0) {
        l++;
    }
    for (int i = l; i <= r; i += 2) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2147483647 - -961633962 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000002,time:1255,execs:454,op:havoc,rep:3)
         * UBSan: signed integer overflow: 2147483647 - -169341384 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000002,time:12295,execs:5259,op:havoc,rep:8)
         */
        if (sum > INT_MAX - i) {
            return 0;
        }
        sum += i;
    }
    return (int)sum;
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
    int result = sum_of_evens(l, r);
    printf("Sum of even numbers between %d and %d is: %d\n", l, r, result);
    return 0;
}