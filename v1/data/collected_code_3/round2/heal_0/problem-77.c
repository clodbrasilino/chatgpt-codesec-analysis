#include <stdio.h>
#include <stdlib.h>

int diffSum(int n) {
    int diff = 0;
    while (n > 0) {
        int digit = n % 10;
        if (digit % 2 == 0) {
            diff += digit;
        } else {
            diff -= digit;
        }
        n /= 10;
    }
    return abs(diff);
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    printf("Difference between sum of even and odd digits: %d\n", diffSum(num));
    return 0;
}