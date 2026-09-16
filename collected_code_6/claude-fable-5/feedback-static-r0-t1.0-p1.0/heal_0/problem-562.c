#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const int *data;
    size_t length;
} Sublist;

size_t max_sublist_length(const Sublist *lists, size_t count)
{
    size_t max_len = 0;
    size_t i;

    if (lists == NULL || count == 0) {
        return 0;
    }

    for (i = 0; i < count; i++) {
        if (lists[i].data != NULL && lists[i].length > max_len) {
            max_len = lists[i].length;
        }
    }

    return max_len;
}

int main(void)
{
    const int a[] = {1, 2, 3};
    const int b[] = {4, 5};
    const int c[] = {6, 7, 8, 9, 10};
    Sublist lists[3];
    size_t result;

    lists[0].data = a;
    lists[0].length = sizeof(a) / sizeof(a[0]);
    lists[1].data = b;
    lists[1].length = sizeof(b) / sizeof(b[0]);
    lists[2].data = c;
    lists[2].length = sizeof(c) / sizeof(c[0]);

    result = max_sublist_length(lists, sizeof(lists) / sizeof(lists[0]));

    if (printf("Maximum sublist length: %zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}