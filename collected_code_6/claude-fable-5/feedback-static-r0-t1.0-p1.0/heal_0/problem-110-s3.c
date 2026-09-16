#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long start;
    long long end;
} Range;

static Range *find_missing_ranges(const long long *nums, size_t count,
                                  long long lower, long long upper,
                                  size_t *result_count)
{
    Range *result = NULL;
    size_t capacity = count + 1U;
    size_t used = 0U;
    long long next = lower;
    size_t i;

    if (result_count == NULL) {
        return NULL;
    }

    *result_count = 0U;

    if (lower > upper) {
        return NULL;
    }

    result = malloc(capacity * sizeof(Range));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0U; i < count; i++) {
        long long value = nums[i];

        if (value < next) {
            continue;
        }
        if (value > upper) {
            break;
        }
        if (value > next) {
            result[used].start = next;
            result[used].end = value - 1;
            used++;
        }
        if (value == upper) {
            next = upper;
            *result_count = used;
            return result;
        }
        next = value + 1;
    }

    if (next <= upper) {
        result[used].start = next;
        result[used].end = upper;
        used++;
    }

    *result_count = used;

    if (used == 0U) {
        free(result);
        return NULL;
    }

    return result;
}

int main(void)
{
    long long nums[] = { 3, 5, 8, 11, 12 };
    size_t count = sizeof(nums) / sizeof(nums[0]);
    long long lower = 1;
    long long upper = 15;
    size_t missing_count = 0U;
    size_t i;
    Range *missing;

    missing = find_missing_ranges(nums, count, lower, upper, &missing_count);

    if (missing == NULL && missing_count == 0U) {
        if (printf("No missing ranges found.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    if (missing == NULL) {
        if (fprintf(stderr, "Memory allocation failed.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    for (i = 0U; i < missing_count; i++) {
        if (missing[i].start == missing[i].end) {
            if (printf("%lld\n", missing[i].start) < 0) {
                free(missing);
                return EXIT_FAILURE;
            }
        } else {
            if (printf("%lld->%lld\n", missing[i].start, missing[i].end) < 0) {
                free(missing);
                return EXIT_FAILURE;
            }
        }
    }

    free(missing);
    return EXIT_SUCCESS;
}