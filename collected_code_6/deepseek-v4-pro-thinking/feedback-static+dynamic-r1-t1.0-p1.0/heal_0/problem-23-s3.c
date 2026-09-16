#include <stddef.h>
#include <stdio.h>

long long max_sum(int **lists, const size_t *lengths, size_t count)
{
    long long max = 0;
    int has_valid = 0;
    size_t i;
    size_t j;

    if (lists == NULL || lengths == NULL || count == 0) {
        return 0;
    }

    for (i = 0; i < count; ++i) {
        long long sum = 0;

        if (lengths[i] == 0) {
            if (!has_valid || max < 0) {
                max = 0;
                has_valid = 1;
            }
            continue;
        }

        if (lists[i] == NULL) {
            continue;
        }

        for (j = 0; j < lengths[i]; ++j) {
            sum += lists[i][j];
        }

        if (!has_valid || sum > max) {
            max = sum;
            has_valid = 1;
        }
    }

    return has_valid ? max : 0;
}

int main(void)
{
    int a[] = {1, 2, 3};
    int b[] = {-1, -2, -3, -4};
    int c[] = {10, 20};
    int d[] = {5, -6, 7};
    int *lists[] = {a, b, c, d};
    size_t lengths[] = {
        sizeof(a) / sizeof(a[0]),
        sizeof(b) / sizeof(b[0]),
        sizeof(c) / sizeof(c[0]),
        sizeof(d) / sizeof(d[0])
    };
    size_t count = sizeof(lists) / sizeof(lists[0]);

    printf("%lld\n", max_sum(lists, lengths, count));

    return 0;
}