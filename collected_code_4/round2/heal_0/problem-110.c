#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Range;

Range *find_missing_ranges(int *nums, int nums_len, int start, int end, int *return_size) {
    Range *missing_ranges = malloc(sizeof(Range) * nums_len);
    *return_size = 0;
    
    if (nums_len == 0) {
        missing_ranges[0].start = start;
        missing_ranges[0].end = end;
        (*return_size)++;
        return missing_ranges;
    }
    
    if (nums[0] > start) {
        missing_ranges[0].start = start;
        missing_ranges[0].end = nums[0] - 1;
        (*return_size)++;
    }
    
    for (int i = 0; i < nums_len - 1; ++i) {
        if (nums[i + 1] - nums[i] > 1) {
            missing_ranges[*return_size].start = nums[i] + 1;
            missing_ranges[*return_size].end = nums[i + 1] - 1;
            (*return_size)++;
        }
    }
    
    if (nums[nums_len - 1] < end) {
        missing_ranges[*return_size].start = nums[nums_len - 1] + 1;
        missing_ranges[*return_size].end = end;
        (*return_size)++;
    }
    
    return missing_ranges;
}

int main() {
    int nums[] = {2, 3, 5, 10};
    int nums_len = sizeof(nums) / sizeof(nums[0]);
    int start = 0;
    int end = 15;
    int return_size = 0;
    
    Range *missing_ranges = find_missing_ranges(nums, nums_len, start, end, &return_size);
    
    for (int i = 0; i < return_size; ++i) {
        printf("Missing range: %d-%d\n", missing_ranges[i].start, missing_ranges[i].end);
    }
    
    free(missing_ranges);
    
    return 0;
}