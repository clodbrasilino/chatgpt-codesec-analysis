#include <stdio.h>
#include <stdbool.h>

bool isDivisibleByAllDigits(int num) {
    int temp = num;
    while (temp > 0) {
        int digit = temp % 10;
        if (digit == 0 || num % digit != 0) {
            return false;
        }
        temp /= 10;
    }
    return true;
}

void findNumbersInRange(int start, int end) {
    printf("Numbers in range [%d, %d] divisible by all their digits:\n", start, end);
    for (int i = start; i <= end; i++) {
        if (isDivisibleByAllDigits(i)) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main(void) {
    int start, end;
    
    printf("Enter start of range: ");
    if (scanf("%d", &start) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    printf("Enter end of range: ");
    if (scanf("%d", &end) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (start > end) {
        printf("Invalid range: start must be less than or equal to end\n");
        return 1;
    }
    
    if (start <= 0) {
        printf("Invalid range: numbers must be positive\n");
        return 1;
    }
    
    findNumbersInRange(start, end);
    
    return 0;
}