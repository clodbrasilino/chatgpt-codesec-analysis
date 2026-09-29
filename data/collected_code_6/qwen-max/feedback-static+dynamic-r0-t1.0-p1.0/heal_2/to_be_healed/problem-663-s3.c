#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_largest_k(int x, int y) {
    if (x <= 0 || y < 0 || y >= x) {
        return -1;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 10 + 2147483640 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:82,execs:45,op:havoc,rep:7)
     */
    return (y + (INT_MAX / x) * x);
}

int main() {
    int x, y;
    printf("Enter the value of x: ");
    scanf("%d", &x);
    printf("Enter the value of y: ");
    scanf("%d", &y);

    int result = find_largest_k(x, y);
    if (result == -1) {
        printf("Invalid input.\n");
    } else {
        printf("The largest possible value of k is: %d\n", result);
    }

    return 0;
}