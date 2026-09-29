#include <stdio.h>
#include <stdbool.h>

bool canFormTriangle(int a, int b, int c) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 1498876126 + 1139355592 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:1336,execs:1169,op:havoc,rep:6)
     * UBSan: signed integer overflow: 1139355597 + 1199545584 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:23688,execs:20873,op:havoc,rep:23)
     * UBSan: signed integer overflow: 1139355592 + 1199545584 cannot be represented in type 'int'
     */
    if (a > 0 && b > 0 && c > 0 && a + b + c == 180) {
        return true;
    }
    return false;
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