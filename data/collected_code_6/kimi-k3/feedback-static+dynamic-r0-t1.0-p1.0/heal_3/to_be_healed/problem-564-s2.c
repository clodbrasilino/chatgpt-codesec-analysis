#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int compare_ints(const void *a, const void *b)
{
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    if (ia < ib) return -1;
    if (ia > ib) return 1;
    return 0;
}

uint64_t count_unequal_pairs(const int *arr, size_t n)
{
    if (arr == NULL || n < 2) {
        return 0;
    }

    uint64_t total = (uint64_t)n * (n - 1) / 2;
    uint64_t equal = 0;

    int *sorted = malloc(n * sizeof(*sorted));
    if (sorted == NULL) {
        return 0;
    }

    for (size_t i = 0; i < n; i++) {
        sorted[i] = arr[i];
    }

    qsort(sorted, n, sizeof(*sorted), compare_ints);

    size_t i = 0;
    while (i < n) {
        size_t j = i + 1;
        while (j < n && sorted[j] == sorted[i]) {
            j++;
        }
        uint64_t freq = (uint64_t)(j - i);
        if (freq > 1) {
            equal += freq * (freq - 1) / 2;
        }
        i = j;
    }

    free(sorted);
    /* Possible weaknesses found:
     * Flawfinder equal: Function does not check the second iterator for over-read conditions (CWE-126). This function is often discouraged by most C++ coding standards in favor of its safer alternatives provided since C++14. Consider using a form of this function that checks the second iterator before potentially overflowing it. (risk 1, buffer)
     */
    return total - equal;
}

int main(void)
{
    int arr[] = {1, 2, 3, 2, 1, 4};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    uint64_t result = count_unequal_pairs(arr, n);
    printf("%llu\n", (unsigned long long)result);

    return 0;
}