#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool canFormTriangle(long a, long b, long c) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 + 70 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:504,execs:489,op:havoc,rep:2)
     */
    if (a > 0 && b > 0 && c > 0 && a + b > c && a + c > b && b + c > a) {
        return true;
    }
    return false;
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