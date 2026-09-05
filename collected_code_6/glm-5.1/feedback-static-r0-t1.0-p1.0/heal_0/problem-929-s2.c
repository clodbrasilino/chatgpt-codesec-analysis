#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *items;
    size_t len;
} Tuple;

int count_repeated_items(Tuple t) {
    if (t.items == NULL || t.len == 0) {
        return 0;
    }

    int *seen = (int *)malloc(t.len * sizeof(int));
    if (seen == NULL) {
        return 0;
    }

    size_t seen_len = 0;
    int repeated_count = 0;

    for (size_t i = 0; i < t.len; i++) {
        int is_seen = 0;
        for (size_t j = 0; j < seen_len; j++) {
            if (seen[j] == t.items[i]) {
                is_seen = 1;
                break;
            }
        }
        if (!is_seen) {
            seen[seen_len++] = t.items[i];
        }
    }

    free(seen);

    for (size_t i = 0; i < seen_len; i++) {
        int current_count = 0;
        for (size_t j = 0; j < t.len; j++) {
            if (seen[i] == t.items[j]) {
                current_count++;
            }
        }
        if (current_count > 1) {
            repeated_count++;
        }
    }

    return repeated_count;
}

int main(void) {
    int data[] = {1, 2, 2, 3, 4, 4, 4, 5};
    Tuple t;
    t.items = data;
    t.len = sizeof(data) / sizeof(data[0]);

    int result = count_repeated_items(t);
    printf("%d\n", result);

    return 0;
}