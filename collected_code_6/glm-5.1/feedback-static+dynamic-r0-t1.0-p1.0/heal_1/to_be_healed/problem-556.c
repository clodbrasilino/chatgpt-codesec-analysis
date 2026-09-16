#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
long long count_odd_xor_pairs(int *arr, size_t n) {
    size_t even_count = 0;
    size_t odd_count = 0;
    size_t i;

    if (arr == NULL || n == 0) {
        return 0;
    }

    for (i = 0; i < n; i++) {
        if ((arr[i] & 1) == 0) {
            even_count++;
        } else {
            odd_count++;
        }
    }

    return (long long)even_count * (long long)odd_count;
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    long long result;

    result = count_odd_xor_pairs(arr, n);

    printf("%lld\n", result);

    return 0;
}