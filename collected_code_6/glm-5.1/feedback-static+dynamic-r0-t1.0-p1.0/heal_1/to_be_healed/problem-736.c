#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
size_t bisect_left(int *arr, size_t size, int value) {
    if (arr == NULL) {
        return 0;
    }
    size_t lo = 0;
    size_t hi = size;
    while (lo < hi) {
        size_t mid = lo + (hi - lo) / 2;
        if (arr[mid] < value) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    return lo;
}

int main(void) {
    int arr[] = {1, 2, 2, 2, 3, 4, 5, 6, 7};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    size_t idx5 = bisect_left(arr, size, 2);
    printf("%zu\n", idx5);

    size_t idx0 = bisect_left(arr, size, 0);
    printf("%zu\n", idx0);

    size_t idx9 = bisect_left(arr, size, 9);
    printf("%zu\n", idx9);

    size_t idxnull = bisect_left(NULL, size, 2);
    printf("%zu\n", idxnull);

    return 0;
}