#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int get_max(int a, int b, int c) {
    int max = a;
    if (b > max) {
        max = b;
    }
    if (c > max) {
        max = c;
    }
    return max;
}

static int get_min(int a, int b, int c) {
    int min = a;
    if (b < min) {
        min = b;
    }
    if (c < min) {
        min = c;
    }
    return min;
}

int find_closest_elements(const int *arr1, size_t len1,
                          const int *arr2, size_t len2,
                          const int *arr3, size_t len3,
                          int *res1, int *res2, int *res3) {
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    long long min_diff = LLONG_MAX;

    if (!arr1 || !arr2 || !arr3 || !res1 || !res2 || !res3) {
        return -1;
    }
    if (len1 == 0 || len2 == 0 || len3 == 0) {
        return -1;
    }

    while (i < len1 && j < len2 && k < len3) {
        int a = arr1[i];
        int b = arr2[j];
        int c = arr3[k];

        int current_min = get_min(a, b, c);
        int current_max = get_max(a, b, c);
        
        long long diff = (long long)current_max - (long long)current_min;

        if (diff < min_diff) {
            min_diff = diff;
            *res1 = a;
            *res2 = b;
            *res3 = c;
        }

        if (diff == 0) {
            break;
        }

        if (a == current_min) {
            i++;
        } else if (b == current_min) {
            j++;
        } else {
            k++;
        }
    }

    return 0;
}

int main(void) {
    int arr1[] = {1, 4, 10};
    int arr2[] = {2, 15, 20};
    int arr3[] = {10, 12};

    size_t len1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t len2 = sizeof(arr2) / sizeof(arr2[0]);
    size_t len3 = sizeof(arr3) / sizeof(arr3[0]);

    int res1 = 0;
    int res2 = 0;
    int res3 = 0;

    if (find_closest_elements(arr1, len1, arr2, len2, arr3, len3, &res1, &res2, &res3) == 0) {
        printf("%d %d %d\n", res1, res2, res3);
    } else {
        fprintf(stderr, "Error: Invalid arguments or empty arrays provided.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}