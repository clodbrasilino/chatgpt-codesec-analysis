#include <stdio.h>
#include <stddef.h>

static int list_equals(const int *a, int len_a, const int *b, int len_b)
{
    if (len_a != len_b) {
        return 0;
    }
    if (len_a == 0) {
        return 1;
    }
    if (a == NULL || b == NULL) {
        return 0;
    }
    for (int i = 0; i < len_a; ++i) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return 1;
}

int count_unique_lists(int **lists, const int *lengths, int count)
{
    if (count < 0) {
        return -1;
    }
    if (count == 0) {
        return 0;
    }
    if (lists == NULL || lengths == NULL) {
        return -1;
    }
    for (int i = 0; i < count; ++i) {
        if (lengths[i] < 0) {
            return -1;
        }
        if (lists[i] == NULL && lengths[i] > 0) {
            return -1;
        }
    }

    int unique = 0;
    for (int i = 0; i < count; ++i) {
        int duplicate = 0;
        for (int j = 0; j < i; ++j) {
            if (list_equals(lists[i], lengths[i], lists[j], lengths[j])) {
                duplicate = 1;
                break;
            }
        }
        if (duplicate == 0) {
            ++unique;
        }
    }
    return unique;
}

int main(void)
{
    int a[] = {1, 2, 3};
    int b[] = {1, 2, 3};
    int c[] = {4, 5};
    int d[] = {1, 2, 3};
    int *lists[] = {a, b, c, d, NULL};
    int lengths[] = {3, 3, 2, 3, 0};
    int count = (int)(sizeof(lists) / sizeof(lists[0]));

    printf("%d\n", count_unique_lists(lists, lengths, count));

    return 0;
}