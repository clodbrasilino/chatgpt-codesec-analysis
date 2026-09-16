#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_min_heap(const int *arr, size_t n)
{
    if (n <= 1) {
        return true;
    }

    if (arr == NULL) {
        return false;
    }

    for (size_t i = 0; i <= (n - 2) / 2; i++) {
        size_t left = 2 * i + 1;
        size_t right = 2 * i + 2;

        if (left < n && arr[i] > arr[left]) {
            return false;
        }
        if (right < n && arr[i] > arr[right]) {
            return false;
        }
    }

    return true;
}

static void report_heap(const char *name, const int *arr, size_t n)
{
    if (is_min_heap(arr, n)) {
        printf("%s is a min heap\n", name);
    } else {
        printf("%s is not a min heap\n", name);
    }
}

int main(void)
{
    int heap1[] = {1, 3, 5, 7, 9, 6, 8};
    int heap2[] = {10, 3, 5, 7, 9, 6, 8};
    int heap3[] = {2};

    struct {
        const char *name;
        const int *arr;
        size_t n;
    } tests[] = {
        {"Array 1", heap1, sizeof(heap1) / sizeof(heap1[0])},
        {"Array 2", heap2, sizeof(heap2) / sizeof(heap2[0])},
        {"Array 3", heap3, sizeof(heap3) / sizeof(heap3[0])},
        {"Empty array", NULL, 0}
    };

    size_t num_tests = sizeof(tests) / sizeof(tests[0]);

    for (size_t i = 0; i < num_tests; i++) {
        report_heap(tests[i].name, tests[i].arr, tests[i].n);
    }

    return EXIT_SUCCESS;
}