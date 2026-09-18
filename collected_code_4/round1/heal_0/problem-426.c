#include <stdio.h>

void filter_odd_numbers(int *arr, int length){
    for(int i = 0; i < length; i++) {
        if(arr[i] % 2 != 0) {
            arr[i] = 0;
        }
    }
}

int main () {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int length = sizeof(numbers) / sizeof(numbers[0]);

    filter_odd_numbers(numbers, length);

    for(int i = 0; i < length; i++) {
        printf("%d ", numbers[i]);
    }

    return 0;
}