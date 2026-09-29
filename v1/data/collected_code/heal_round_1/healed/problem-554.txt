#include <stdio.h>

void findOddNumbers(const int arr[], int size) {
    printf("Odd numbers in the list: ");
    
    for(int i = 0; i < size; i++) {
        if(arr[i] % 2 != 0) {
            printf("%d ", arr[i]);
        }
    }
}

int main() {
    int nums[] = {2, 7, 10, 15, 8, 3, 6};
    int size = sizeof(nums) / sizeof(nums[0]);

    findOddNumbers(nums, size);

    return 0;
}