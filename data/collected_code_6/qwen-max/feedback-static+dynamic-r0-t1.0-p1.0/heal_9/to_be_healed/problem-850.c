#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool canFormTriangle(long a, long b, long c) {
    if (a <= 0 || b <= 0 || c <= 0) return false;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 + 1073741824 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000005,time:632,execs:642,op:havoc,rep:2)
     */
    if (a > INT_MAX - b && a > b + c) return false;
    if (b > INT_MAX - a && b > a + c) return false;
    if (c > INT_MAX - a && c > a + b) return false;
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