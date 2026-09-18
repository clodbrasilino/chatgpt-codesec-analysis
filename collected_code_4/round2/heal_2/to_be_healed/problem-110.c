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
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'missing_ranges' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        missing_ranges[0].start = start;
        missing_ranges[0].end = end;
        return missing_ranges;
    }

    int temp_size = nums_len + 1;
    Range *temp_ranges = (Range *)malloc(sizeof(Range) * temp_size);
    int count = 0;

    if (nums[0] > start) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'temp_ranges' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        temp_ranges[count].start = start;
        temp_ranges[count].end = nums[0] - 1;
        count++;
    }

    for (int i = 0; i < nums_len - 1; ++i) {
        if (nums[i + 1] - nums[i] > 1) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'temp_ranges' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            temp_ranges[count].start = nums[i] + 1;
            temp_ranges[count].end = nums[i + 1] - 1;
            count++;
        }
    }

    if (nums[nums_len - 1] < end) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'temp_ranges' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        temp_ranges[count].start = nums[nums_len - 1] + 1;
        temp_ranges[count].end = end;
        count++;
    }

    *return_size = count;
    
    Range *missing_ranges = (Range *)malloc(sizeof(Range) * (*return_size));
    for (int i = 0; i < *return_size; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'missing_ranges' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
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
    for (int i = 0; i < return_size; ++i) {
        /* Possible weaknesses found:
         *  use of uninitialized value '*missing_ranges_22 + _2.end' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         *  dereference of possibly-NULL 'missing_ranges' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        printf("Missing range: %d-%d\n", missing_ranges[i].start, missing_ranges[i].end);
    }
    
    free(missing_ranges);
    
    return 0;
}