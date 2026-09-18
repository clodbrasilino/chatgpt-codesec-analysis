#include <stdio.h>
#include <limits.h>

int findLargest(int nums[], int arrSize){
    int max = INT_MIN;
    
    for (int i =0; i < arrSize; i++){
        if (nums[i] > max){
            max = nums[i];
        }
    }
  
  return (max > 0) ? max : -1;
}

int main() {
    int arrSize;
    printf("Enter array size: ");
    scanf("%d", &arrSize);
    
    if(arrSize <= 0) {
        printf("Enter valid array size\n");
        return 0;
    }

    int nums[arrSize];

    printf("Enter array elements: ");
    for(int i = 0; i < arrSize; i++) {
        scanf("%d", &nums[i]);
    }

    int largest = findLargest(nums, arrSize);

    if(largest == -1) {
        printf("No positive numbers in the array\n");
    }
    else {
        printf("Largest positive number is %d\n", largest);
    }

    return 0;
}