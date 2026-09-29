#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool isDifferenceOfSquares(long n) {
    if (n < 0) return false;
    long x = 0, y = 1;
    while (x <= y) {
        long diff = y * y - x * x;
        if (diff == n) {
            return true;
        } else if (diff < n) {
            if (y < LONG_MAX / 2) y++;
            else break;
        } else {
            x++;
        }
    }
    return false;
}

int main() {
    long num;
    printf("Enter a number: ");
    scanf("%ld", &num);
    if (isDifferenceOfSquares(num)) {
        printf("Can be represented as difference of two squares.\n");
    } else {
        printf("Cannot be represented as difference of two squares.\n");
    }
    return 0;
}