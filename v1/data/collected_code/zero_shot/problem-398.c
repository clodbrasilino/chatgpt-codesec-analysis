#include <stdio.h>

int sumOfDigits(int number) {
    int sum = 0;
    while(number > 0) {
        sum += number % 10;
        number /= 10;
    }
    return sum;
}

void computeSumOfDigits(int list[], int length) {
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