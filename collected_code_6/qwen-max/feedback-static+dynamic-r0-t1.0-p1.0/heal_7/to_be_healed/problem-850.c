#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool canFormTriangle(long a, long b, long c) {
    if (a <= 0 || b <= 0 || c <= 0) return false;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 + 70 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000003,time:2195,execs:2108,op:havoc,rep:2)
     */
    if (a > b + c || b > a + c || c > a + b) return false;
    if (a > LONG_MAX - b || a > LONG_MAX - c || b > LONG_MAX - a || b > LONG_MAX - c || c > LONG_MAX - a || c > LONG_MAX - b) return false;
    return true;
}

int main() {
    long side1, side2, side3;
    printf("Enter three sides of a triangle: ");
    scanf("%ld %ld %ld", &side1, &side2, &side3);

    if (canFormTriangle(side1, side2, side3)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}