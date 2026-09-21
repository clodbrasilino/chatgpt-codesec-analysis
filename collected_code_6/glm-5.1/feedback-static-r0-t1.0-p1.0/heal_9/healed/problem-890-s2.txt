#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

static long safe_strtol(const char *str) {
    char *endptr;
    errno = 0;
    long val = strtol(str, &endptr, 10);
    if (errno != 0 || *endptr != '\0' || val <= 0 || val > INT_MAX) {
        return -1;
    }
    return val;
}

int find_extra_element_index(const int *arr1, const int *arr2, int n) {
    int low = 0;
    int high = n - 2;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr1[mid] == arr2[mid]) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return low;
}

int main(int argc, char * const argv[]) {
    int arr1[] = {2, 4, 6, 8, 10, 12, 13};
    int arr2[] = {2, 4, 6, 8, 10, 12};
    int n1 = (int)(sizeof(arr1) / sizeof(arr1[0]));
    int n2 = (int)(sizeof(arr2) / sizeof(arr2[0]));

    if (argc > 1) {
        long val = safe_strtol(argv[1]);
        if (val < 0) return EXIT_FAILURE;
        n1 = (int)val;
        
        if (argc > 2) {
            val = safe_strtol(argv[2]);
            if (val < 0) return EXIT_FAILURE;
            n2 = (int)val;
        }
    }

    if (n1 <= 0 || n2 <= 0) {
        return EXIT_FAILURE;
    }

    const int *longer_arr;
    const int *shorter_arr;
    int longer_n;

    if (n1 > n2) {
        longer_arr = arr1;
        shorter_arr = arr2;
        longer_n = n1;
    } else if (n2 > n1) {
        longer_arr = arr2;
        shorter_arr = arr1;
        longer_n = n2;
    } else {
        return EXIT_FAILURE;
    }

    int index = find_extra_element_index(longer_arr, shorter_arr, longer_n);
    printf("%d\n", index);

    return EXIT_SUCCESS;
}