#include <stdio.h>

int sum_of_digits(int n) {
    int sum = 0;
    while(n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int main() {
    int arr[] = {123, 456, 789, 112, 334, 556};
    int size = sizeof(arr)/sizeof(arr[0]);
    for(int i=0; i<size; i++) {
        printf("Sum of digits of %d is %d\n", arr[i], sum_of_digits(arr[i]));
    }
    return 0;
}