#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool canFormTriangle(long a, long b, long c) {
    if (a <= 0 || b <= 0 || c <= 0) return false;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 330 + 9223372036854775807 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000003,time:805,execs:928,op:havoc,rep:2)
     */
    if (a > LONG_MAX - b || a > b + c) return false;
    if (b > LONG_MAX - a || b > a + c) return false;
    if (c > LONG_MAX - a || c > a + b) return false;
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