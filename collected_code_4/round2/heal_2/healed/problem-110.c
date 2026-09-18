#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Range;

Range *find_missing_ranges(int *nums, int nums_len, int start, int end, int *return_size) {
    if (nums_len == 0) {
        *return_size = 1;
        Range *missing_ranges = (Range *)malloc(sizeof(Range) * (*return_size));
        if (missing_ranges == NULL) 
            return NULL;

        missing_ranges[0].start = start;
        missing_ranges[0].end = end;

        return missing_ranges;
    }

    int temp_size = nums_len + 1;
    Range *temp_ranges = (Range *)malloc(sizeof(Range) * temp_size);

    if (temp_ranges == NULL) 
        return NULL;
    
    int count = 0;

    if (nums[0] > start) {
        temp_ranges[count].start = start;
        temp_ranges[count].end = nums[0] - 1;
        count++;
    }

    for (int i = 0; i < nums_len - 1; ++i) {
        if (nums[i + 1] - nums[i] > 1) {
            temp_ranges[count].start = nums[i] + 1;
            temp_ranges[count].end = nums[i + 1] - 1;
            count++;
        }
    }

    if (nums[nums_len - 1] < end) {
        temp_ranges[count].start = nums[nums_len - 1] + 1;
        temp_ranges[count].end = end;
        count++;
    }

    *return_size = count;
    
    Range *missing_ranges = (Range *)malloc(sizeof(Range) * (*return_size));

    if (missing_ranges == NULL) {
        free(temp_ranges);
        return NULL;
    }

    for (int i = 0; i < *return_size; i++) {
        missing_ranges[i] = temp_ranges[i];
    }

    free(temp_ranges);

    return missing_ranges;
}

int main() {
    int nums[] = {2, 3, 5, 10};
    int nums_len = sizeof(nums) / sizeof(nums[0]);
    int start = 0;
    int end = 15;
    int return_size = 0;
    
    Range *missing_ranges = find_missing_ranges(nums, nums_len, start, end, &return_size);

    if (missing_ranges == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < return_size; ++i) {
        printf("Missing range: %d-%d\n", missing_ranges[i].start, missing_ranges[i].end);
    }
    
    free(missing_ranges);
    
    return 0;
}