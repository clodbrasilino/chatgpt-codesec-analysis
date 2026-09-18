#include <stdlib.h>
#include <stdbool.h>

int compare(const void * a, const void * b) {
    return (*(int*)a - *(int*)b);
}

bool containsDuplicate(int* nums, int numsSize){
    int i;
    qsort(nums, numsSize, sizeof(int), compare);
    for(i = 0; i < numsSize - 1; i++){
        if(nums[i] == nums[i+1]){
            return true;
        }
    }
    return false;
}

int main()
{
    int nums[] = {1,2,3,4,5,6,7,8,9,0,1};
    int size = sizeof(nums)/sizeof(nums[0]); 
    bool result = containsDuplicate(nums,size);
    if(result){
        printf("Array contains duplicate values\n");
    }else{
        printf("Array doesn't contain any duplicate values\n");
    }
    return 0;
}