#include<stdio.h>

int countDigits(int num) {
    int count = 0;
    while(num != 0) {
        num /= 10;
        count++;
    }
    return count;
}

int main() {
    int number = 12345;
    int digitCount = countDigits(number);
    printf("Number of digits: %d", digitCount);
    return 0;
}