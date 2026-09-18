#include <stdio.h>

int sum_of_evens(int l, int r) {
    int sum = 0;
    if (l > r) {
        return sum;
    }
    if (l % 2 != 0) {
        l++;
    }
    for (int i = l; i <= r; i += 2) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2147441938 + 92682 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000002,time:1476,execs:636,op:havoc,rep:1)
         * UBSan: signed integer overflow: -1405424328 + -1405424326 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000002,time:1311,execs:570,op:havoc,rep:8)
         */
        sum += i;
    }
    return sum;
}

int main() {
    int l, r;
    printf("Enter the range (l and r): ");
    scanf("%d %d", &l, &r);
    int result = sum_of_evens(l, r);
    printf("Sum of even numbers between %d and %d is: %d\n", l, r, result);
    return 0;
}