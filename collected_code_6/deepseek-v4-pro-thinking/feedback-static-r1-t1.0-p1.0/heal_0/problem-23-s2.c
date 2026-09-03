#include <limits.h>
#include <stddef.h>
#include <stdio.h>

typedef struct {
    const int *data;
    size_t length;
} IntList;

long long max_list_sum(const IntList *lists, size_t count, int *error) {
    if (lists == NULL || count == 0) {
        if (error != NULL) {
            *error = -1;
        }
        return 0;
    }

    long long max_sum = LLONG_MIN;

    for (size_t i = 0; i < count; ++i) {
        if (lists[i].data == NULL && lists[i].length > 0) {
            if (error != NULL) {
                *error = -2;
            }
            return 0;
        }

        long long sum = 0;
        for (size_t j = 0; j < lists[i].length; ++j) {
            sum += lists[i].data[j];
        }

        if (sum > max_sum) {
            max_sum = sum;
        }
    }

    if (error != NULL) {
        *error = 0;
    }

    return max_sum;
}

int main(void) {
    int a[] = {1, 2, 3};
    int b[] = {-5, 10};
    int c[] = {7, -2, 0, 4};

    IntList lists[] = {
        {a, sizeof(a) / sizeof(a[0])},
        {b, sizeof(b) / sizeof(b[0])},
        {c, sizeof(c) / sizeof(c[0])}
    };

    int error = 0;
    long long result = max_list_sum(lists, sizeof(lists) / sizeof(lists[0]), &error);

    if (error != 0) {
        return 1;
    }

    printf("%lld\n", result);
    return 0;
}