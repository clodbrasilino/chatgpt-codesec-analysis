#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool canFormTriangle(int a, int b, int c) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 1115752192 + 1139355592 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000002,time:1342,execs:1432,op:havoc,rep:14)
     * UBSan: signed integer overflow: 1139355592 + 1199545584 cannot be represented in type 'int'
     */
    if (a > 0 && b > 0 && c > 0 && a + b > c && a + c > b && b + c > a) {
        return true;
    }
    return false;
}

int main() {
    int side1, side2, side3;
    printf("Enter three sides of a triangle: ");
    scanf("%d %d %d", &side1, &side2, &side3);

    if (canFormTriangle(side1, side2, side3)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}