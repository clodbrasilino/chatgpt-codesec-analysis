#include <stdio.h>
#include <stdbool.h>

bool canFormTriangle(int a, int b, int c) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 1260588339 + 1383020766 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:24807,execs:9648,op:havoc,rep:3)
     */
    return (a + b + c == 180) && (a > 0) && (b > 0) && (c > 0);
}

int main() {
    int angle1, angle2, angle3;
    printf("Enter three angles of a triangle: ");
    if (scanf("%d %d %d", &angle1, &angle2, &angle3) != 3) {
        printf("Invalid input\n");
        return 1;
    }

    if (canFormTriangle(angle1, angle2, angle3)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}