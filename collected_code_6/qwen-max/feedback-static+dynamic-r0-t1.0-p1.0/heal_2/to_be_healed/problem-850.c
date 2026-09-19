#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool canFormTriangle(int a, int b, int c) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 2147483647 - -407995279 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:132,execs:135,op:havoc,rep:5)
     * UBSan: signed integer overflow: 2147483647 - -1 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:233,execs:222,op:havoc,rep:1)
     */
    if (a > INT_MAX - b || a > INT_MAX - c || b > INT_MAX - c) return false;
    return (a + b + c == 180) && (a > 0) && (b > 0) && (c > 0);
}

int main() {
    int angle1, angle2, angle3;
    printf("Enter three angles of a triangle: ");
    scanf("%d %d %d", &angle1, &angle2, &angle3);

    if (canFormTriangle(angle1, angle2, angle3)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}