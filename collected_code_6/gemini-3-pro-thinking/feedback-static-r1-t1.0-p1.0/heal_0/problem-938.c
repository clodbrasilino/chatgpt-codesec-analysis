#include <stdio.h>
#include <limits.h>
#include <stddef.h>

int find_closest_elements(const int *arr1, size_t len1,
                          const int *arr2, size_t len2,
                          const int *arr3, size_t len3,
                          int *res1, int *res2, int *res3) {
    if (!arr1 || !arr2 || !arr3 || !res1 || !res2 || !res3) {
        return -1;
    }
    if (len1 == 0 || len2 == 0 || len3 == 0) {
        return -1;
    }

    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    int min_diff = INT_MAX;

    while (i < len1 && j < len2 && k < len3) {
        int val1 = arr1[i];
        int val2 = arr2[j];
        int val3 = arr3[k];

        int min_val = val1;
        int max_val = val1;

        if (val2 < min_val) {
            min_val = val2;
        }
        if (val3 < min_val) {
            min_val = val3;
        }

        if (val2 > max_val) {
            max_val = val2;
        }
        if (val3 > max_val) {
            max_val = val3;
        }

        int diff = max_val - min_val;

        if (diff < min_diff) {
            min_diff = diff;
            *res1 = val1;
            *res2 = val2;
            *res3 = val3;
        }

        if (min_diff == 0) {
            break;
        }

        if (min_val == val1) {
            i++;
        } else if (min_val == val2) {
            j++;
        } else {
            k++;
        }
    }

    return 0;
}

int main(void) {
    int arr1[] = {1, 4, 10, 15};
    int arr2[] = {2, 11, 20};
    int arr3[] = {10, 12, 15};

    size_t len1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t len2 = sizeof(arr2) / sizeof(arr2[0]);
    size_t len3 = sizeof(arr3) / sizeof(arr3[0]);

    int res1 = 0;
    int res2 = 0;
    int res3 = 0;

    int status = find_closest_elements(arr1, len1, arr2, len2, arr3, len3, &res1, &res2, &res3);

    if (status == 0) {
        printf("%d %d %d\n", res1, res2, res3);
    } else {
        fprintf(stderr, "Error processing arrays\n");
        return 1;
    }

    return 0;
}