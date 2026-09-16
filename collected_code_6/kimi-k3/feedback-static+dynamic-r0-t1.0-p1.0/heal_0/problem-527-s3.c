#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct {
    int first;
    int second;
} Pair;

static int compare_ints(const void *a, const void *b)
{
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;

    if (arg1 < arg2) {
        return -1;
    }
    if (arg1 > arg2) {
        return 1;
    }
    return 0;
}

Pair *find_pairs(const int *arr, size_t size, int target, size_t *pair_count)
{
    int *sorted;
    Pair *pairs;
    size_t left;
    size_t right;
    size_t count;
    size_t capacity;

    if (arr == NULL || pair_count == NULL || size < 2) {
        if (pair_count != NULL) {
            *pair_count = 0;
        }
        return NULL;
    }

    *pair_count = 0;
    capacity = 16;
    count = 0;

    sorted = malloc(size * sizeof(*sorted));
    if (sorted == NULL) {
        return NULL;
    }

    pairs = malloc(capacity * sizeof(*pairs));
    if (pairs == NULL) {
        free(sorted);
        return NULL;
    }

    memcpy(sorted, arr, size * sizeof(*sorted));
    qsort(sorted, size, sizeof(*sorted), compare_ints);

    left = 0;
    right = size - 1;

    while (left < right) {
        long long sum = (long long)sorted[left] + (long long)sorted[right];

        if (sum == target) {
            if (count >= capacity) {
                size_t new_capacity = capacity * 2;
                Pair *temp = realloc(pairs, new_capacity * sizeof(*temp));
                if (temp == NULL) {
                    free(pairs);
                    free(sorted);
                    return NULL;
                }
                pairs = temp;
                capacity = new_capacity;
            }
            pairs[count].first = sorted[left];
            pairs[count].second = sorted[right];
            count++;

            while (left < right && sorted[left] == sorted[left + 1]) {
                left++;
            }
            while (left < right && sorted[right] == sorted[right - 1]) {
                right--;
            }
            left++;
            if (right > 0) {
                right--;
            }
        } else if (sum < target) {
            left++;
        } else {
            if (right > 0) {
                right--;
            } else {
                break;
            }
        }
    }

    free(sorted);

    if (count == 0) {
        free(pairs);
        return NULL;
    }

    *pair_count = count;
    return pairs;
}

int main(void)
{
    int arr[] = {1, 5, 7, -1, 5, 3, 2, 8, 4, 6, 0, 9, 2};
    size_t arr_size = sizeof(arr) / sizeof(arr[0]);
    int target = 6;
    size_t pair_count = 0;
    Pair *pairs;
    size_t i;

    pairs = find_pairs(arr, arr_size, target, &pair_count);

    if (pairs == NULL && pair_count == 0) {
        printf("No pairs found with sum %d\n", target);
        return EXIT_SUCCESS;
    }

    if (pairs == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Pairs with sum %d:\n", target);
    for (i = 0; i < pair_count; i++) {
        printf("(%d, %d)\n", pairs[i].first, pairs[i].second);
    }

    free(pairs);
    return EXIT_SUCCESS;
}