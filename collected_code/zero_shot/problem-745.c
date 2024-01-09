#include <stdio.h>

int isDivisibleByDigits(int num) {
    int temp = num;
    while (temp > 0) {
        int digit = temp % 10;
        if (digit != 0 && num % digit != 0) {
            return 0;
        }
        temp /= 10;
    }
    return 1;
}

void findNumbersInRange(int lower, int upper) {
    printf("Numbers divisible by every digit they contain within the range of %d to %d:\n", lower, upper);
    for (int i = lower; i <= upper; i++) {
        if (isDivisibleByDigits(i)) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main() {
    int lower, upper;
    printf("Enter the lower bound of the range: ");
    scanf("%d", &lower);
    printf("Enter the upper bound of the range: ");
    scanf("%d", &upper);
    findNumbersInRange(lower, upper);
    return 0;
}