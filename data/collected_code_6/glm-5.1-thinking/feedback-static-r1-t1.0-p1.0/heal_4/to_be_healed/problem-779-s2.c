#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int *data;
    size_t size;
} List;

bool are_lists_equal(const List *a, const List *b) {
    if (a == NULL || b == NULL) {
        return false;
    }
    if (a->size != b->size) {
        return false;
    }
    if (a->size == 0) {
        return true;
    }
    if (a->data == NULL || b->data == NULL) {
        return false;
    }
    for (size_t i = 0; i < a->size; i++) {
        if (a->data[i] != b->data[i]) {
            return false;
        }
    }
    return true;
}

size_t count_unique_lists(const List *lists, size_t num_lists) {
    if (lists == NULL || num_lists == 0) {
        return 0;
    }
    size_t count = 0;
    for (size_t i = 0; i < num_lists; i++) {
        bool is_unique = true;
        for (size_t j = 0; j < i; j++) {
            if (are_lists_equal(&lists[i], &lists[j])) {
                is_unique = false;
                break;
            }
        }
        if (is_unique) {
            count++;
        }
    }
    return count;
}

List create_list(const int *src, size_t size) {
    List l;
    l.size = 0;
    l.data = NULL;
    if (size > 0 && src != NULL) {
        if (size > SIZE_MAX / sizeof(int)) {
            return l;
        }
        size_t total_size = size * sizeof(int);
        l.data = malloc(total_size);
        if (l.data != NULL) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(l.data, src, total_size);
            l.size = size;
        }
    }
    return l;
}

void free_lists(List *lists, size_t num_lists) {
    if (lists != NULL) {
        for (size_t i = 0; i < num_lists; i++) {
            free(lists[i].data);
            lists[i].data = NULL;
            lists[i].size = 0;
        }
        free(lists);
    }
}

int main(void) {
    const int d0[] = {1, 2, 3};
    const int d1[] = {1, 2, 3};
    const int d2[] = {4, 5};
    const int d3[] = {1, 2};

    size_t num_lists = 5;
    List *lists = malloc(num_lists * sizeof(List));
    if (lists == NULL) {
        return EXIT_FAILURE;
    }

    lists[0] = create_list(d0, 3);
    lists[1] = create_list(d1, 3);
    lists[2] = create_list(d2, 2);
    lists[3] = create_list(d3, 2);
    lists[4] = create_list(NULL, 0);

    size_t unique_count = count_unique_lists(lists, num_lists);
    printf("%zu\n", unique_count);

    free_lists(lists, num_lists);

    return EXIT_SUCCESS;
}