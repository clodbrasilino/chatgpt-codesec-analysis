#include <stdio.h>

int add_consec_numbers(int arr[], int size) {
    int i, sum = 0;
    for (i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    int sum = add_consec_numbers(arr, size);
    printf("The sum of consecutive numbers is: %d\n", sum);
    return 0;
}