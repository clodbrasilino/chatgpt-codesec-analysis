#include <stdio.h>

int sumOfDigits(int num) {
    int sum = 0;
    while(num != 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

void sumOfDigitsInList(int arr[], int size) {
    for(int i = 0; i < size; i++) {
        printf("Sum of digits of %d is %d\n", arr[i], sumOfDigits(arr[i]));
    }
}

int main() {
    int arr[] = {123, 456, 789, 321};
    int size = sizeof(arr) / sizeof(arr[0]);
    sumOfDigitsInList(arr, size);
    return 0;
}