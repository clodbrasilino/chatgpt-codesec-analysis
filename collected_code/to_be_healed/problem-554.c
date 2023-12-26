#include <stdio.h>

void findOddNumbers(int arr[], int size) {
    printf("Odd numbers in the list: ");
    
    for(int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if(arr[i] % 2 != 0) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
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