#include <stdio.h>
#include <stdbool.h>

bool canFormTriangle(int angle1, int angle2, int angle3) {
    if (angle1 <= 0 || angle2 <= 0 || angle3 <= 0) {
        return false;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 1139355592 + 1199545584 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000000,time:33719,execs:13655,op:havoc,rep:1)
     * UBSan: signed integer overflow: 1139355592 + 1199545584 cannot be represented in type 'int'
     */
    if (angle1 + angle2 + angle3 != 180) {
        return false;
    }
    return true;
}

int main() {
    int a1, a2, a3;
    printf("Enter three angles of a triangle: ");
    scanf("%d %d %d", &a1, &a2, &a3);
    if (canFormTriangle(a1, a2, a3)) {
        printf("A triangle can be formed with these angles.\n");
    } else {
        printf("A triangle cannot be formed with these angles.\n");
    }
    return 0;
}