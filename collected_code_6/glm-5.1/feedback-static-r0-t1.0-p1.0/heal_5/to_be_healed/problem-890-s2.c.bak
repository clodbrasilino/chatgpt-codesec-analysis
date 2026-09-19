#include <stdio.h>
#include <stdlib.h>

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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int arr1[] = {2, 4, 6, 8, 10, 12, 13};
    int arr2[] = {2, 4, 6, 8, 10, 12};
    int n1 = (int)(sizeof(arr1) / sizeof(arr1[0]));
    int n2 = (int)(sizeof(arr2) / sizeof(arr2[0]));

    if (argc > 1) {
        n1 = atoi(argv[1]);
        if (argc > 2) {
            n2 = atoi(argv[2]);
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