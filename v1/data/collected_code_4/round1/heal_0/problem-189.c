#include <stdio.h>

int firstMissingPositive(int* nums, int numsSize) {
    int i;
    for(i = 0; i < numsSize; i++){
        while(nums[i] > 0 && nums[i] <= numsSize && nums[nums[i]-1] != nums[i]){
            int temp = nums[i];
            nums[i] = nums[nums[i]-1];
            nums[temp-1] = temp;
        }
    }
    
    for(i = 0; i< numsSize; i++){
        if(nums[i] != i+1){
            return i+1;
        }
    }
    
    return numsSize+1;
}

int main(void) {
    int test[] = {1,2,0};
    int size = sizeof(test)/sizeof(test[0]);
    int result = firstMissingPositive(test, size);
    
    printf("The first missing positive number is: %d\n", result);
    return 0;
}