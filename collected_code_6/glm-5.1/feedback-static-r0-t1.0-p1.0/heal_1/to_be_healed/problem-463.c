#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'nums' can be declared as pointer to const [constParameterPointer]
 */
int maxProductSubarray(int* nums, int numsSize, int* start, int* end) {
    if (nums == NULL || numsSize <= 0 || start == NULL || end == NULL) {
        return 0;
    }

    int max_prod = nums[0];
    int min_prod = nums[0];
    int result = nums[0];
    
    int current_start_max = 0;
    int current_start_min = 0;
    int global_start = 0;
    int global_end = 0;

    for (int i = 1; i < numsSize; i++) {
        if (nums[i] < 0) {
            int temp_prod = max_prod;
            max_prod = min_prod;
            min_prod = temp_prod;
            
            int temp_start = current_start_max;
            current_start_max = current_start_min;
            current_start_min = temp_start;
        }

        if (nums[i] > max_prod * nums[i]) {
            max_prod = nums[i];
            current_start_max = i;
        } else {
            max_prod = max_prod * nums[i];
        }

        if (nums[i] < min_prod * nums[i]) {
            min_prod = nums[i];
            current_start_min = i;
        } else {
            min_prod = min_prod * nums[i];
        }

        if (max_prod > result) {
            result = max_prod;
            global_start = current_start_max;
            global_end = i;
        }
    }

    *start = global_start;
    *end = global_end;
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char* argv[]) {
    if (argc < 2) {
        return 1;
    }

    int numsSize = argc - 1;
    int* nums = (int*)malloc(numsSize * sizeof(int));
    if (nums == NULL) {
        return 1;
    }

    for (int i = 0; i < numsSize; i++) {
        nums[i] = atoi(argv[i + 1]);
    }

    int start = 0;
    int end = 0;
    int max_prod = maxProductSubarray(nums, numsSize, &start, &end);

    printf("Maximum Product: %d\n", max_prod);
    printf("Subarray indices: [%d, %d]\n", start, end);
    printf("Subarray: ");
    for (int i = start; i <= end; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");

    free(nums);
    return 0;
}