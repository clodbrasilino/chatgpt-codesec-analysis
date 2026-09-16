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
    int curr_start = 0;
    int max_start = 0;
    int max_end = 0;

    for (int i = 1; i < numsSize; i++) {
        if (nums[i] < 0) {
            int temp = max_prod;
            max_prod = min_prod;
            min_prod = temp;
        }

        if (nums[i] > max_prod * nums[i]) {
            max_prod = nums[i];
            curr_start = i;
        } else {
            max_prod = max_prod * nums[i];
        }

        if (nums[i] < min_prod * nums[i]) {
            min_prod = nums[i];
        } else {
            min_prod = min_prod * nums[i];
        }

        if (max_prod > result) {
            result = max_prod;
            max_start = curr_start;
            max_end = i;
        }
    }

    *start = max_start;
    *end = max_end;
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
    int max_product = maxProductSubarray(nums, numsSize, &start, &end);

    printf("Maximum Product: %d\n", max_product);
    printf("Subarray indices: [%d, %d]\n", start, end);
    printf("Subarray: ");
    for (int i = start; i <= end; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");

    free(nums);
    nums = NULL;

    return 0;
}