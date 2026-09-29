#include <stdio.h>
#include <stdlib.h>

int isDivisibleByDigits(int num) {
    if (num == 0) {
        return 0;
    }
    
    int temp = num;
    if (temp < 0) {
        temp = -temp;
    }
    
    while (temp > 0) {
        int digit = temp % 10;
        if (digit == 0 || num % digit != 0) {
            return 0;
        }
        temp /= 10;
    }
    
    return 1;
}

void findNumbersInRange(int start, int end) {
    if (start > end) {
        int temp = start;
        start = end;
        end = temp;
    }
    
    for (int i = start; i <= end; i++) {
        if (isDivisibleByDigits(i)) {
            printf("%d\n", i);
        }
    }
}

int main(void) {
    int start = 1;
    int end = 30;
    
    findNumbersInRange(start, end);
    
    return EXIT_SUCCESS;
}