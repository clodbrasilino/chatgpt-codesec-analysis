#include <stdio.h>
#include <stddef.h>

typedef struct {
    const int *data;
    size_t length;
} List;

int max_list_sum(const List *lists, size_t count) {
    int max_sum = 0;
    int sum = 0;
    int has_valid = 0;
    size_t i;
    size_t j;

    if (lists == NULL || count == 0) {
        return 0;
    }

    for (i = 0; i < count; ++i) {
        if (lists[i].data == NULL || lists[i].length == 0) {
            continue;
        }

        sum = 0;
        for (j = 0; j < lists[i].length; ++j) {
            sum += lists[i].data[j];
        }

        if (!has_valid || sum > max_sum) {
            max_sum = sum;
            has_valid = 1;
        }
    }

    return max_sum;
}

int main(void) {
    int row0[] = {1, 2, 3};
    int row1[] = {-1, 5, 2};
    int row2[] = {7, -4};

    List lists[] = {
        {row0, sizeof(row0) / sizeof(row0[0])},
        {row1, sizeof(row1) / sizeof(row1[0])},
        {row2, sizeof(row2) / sizeof(row2[0])}
    };

    printf("%d\n", max_list_sum(lists, sizeof(lists) / sizeof(lists[0])));

    return 0;
}