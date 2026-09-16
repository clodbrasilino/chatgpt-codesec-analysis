#include <stdio.h>
#include <stdbool.h>

bool isSumOfPowersOfTwo(int n) {
    if (n <= 0) return false;
    while (n > 0) {
        if (n & 1) n--;
        if (n & 1) return false;
        n >>= 1;
    }
    return true;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    if (isSumOfPowersOfTwo(num)) {
        printf("The number can be represented as sum of non-zero powers of 2.\n");
    } else {
        printf("The number cannot be represented as sum of non-zero powers of 2.\n");
    }
    return 0;
}