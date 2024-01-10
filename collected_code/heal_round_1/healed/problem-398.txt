#include <stdio.h>

int sumOfDigits(const int number) {
    int sum = 0;
    int num = number;
    while(num > 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

void computeSumOfDigits(const int list[], const int length) {
    for(int i = 0; i < length; i++) {
        int sum = sumOfDigits(list[i]);
        printf("Sum of digits in number %d: %d\n", list[i], sum);
    }
}

int main() {
    int list[] = {123, 456, 789};
    int length = sizeof(list) / sizeof(list[0]);
    computeSumOfDigits(list, length);
    return 0;
}