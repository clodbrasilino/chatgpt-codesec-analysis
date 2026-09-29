#include <stdio.h>
#include <stdbool.h>

bool canFormTriangle(int a, int b, int c) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 1073741824 + 1139355592 cannot be represented in type 'int'
     * UBSan: signed integer overflow: 1139355592 + 1199545584 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:7815,execs:3013,op:havoc,rep:4)
     */
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