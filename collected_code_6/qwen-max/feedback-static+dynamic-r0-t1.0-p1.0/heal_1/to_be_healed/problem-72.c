#include <stdio.h>
#include <stdbool.h>

bool isDifferenceOfSquares(int n) {
    if (n < 0) return false;
    int x = 0, y = 1;
    while (x <= y) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 46341 * 46341 cannot be represented in type 'int'
         * UBSan: signed integer overflow: -2147479015 - 947900944 cannot be represented in type 'int'
         */
        int diff = y * y - x * x;
        if (diff == n) {
            return true;
        } else if (diff < n) {
            y++;
        } else {
            x++;
        }
    }
    return false;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    if (isDifferenceOfSquares(num)) {
        printf("Can be represented as difference of two squares.\n");
    } else {
        printf("Cannot be represented as difference of two squares.\n");
    }
    return 0;
}