#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int *data;
    int len;
} List;

int compare_ints(const void *a, const void *b) {
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    return (ia > ib) - (ia < ib);
}

int list_equal(const void *a, const void *b) {
    const List *la = (const List *)a;
    const List *lb = (const List *)b;
    if (la->len != lb->len) {
        return 0;
    }
    for (int i = 0; i < la->len; i++) {
        if (la->data[i] != lb->data[i]) {
            return 0;
        }
    }
    return 1;
}

int count_unique_lists(List *lists, int count) {
    if (lists == NULL || count <= 0) {
        return 0;
    }

    List *sorted_lists = (List *)malloc((size_t)count * sizeof(List));
    if (sorted_lists == NULL) {
        return 0;
    }

    size_t total_alloc = 0;
    int use_bulk = 0;
    void *bulk = NULL;

    for (int i = 0; i < count; i++) {
        if (lists[i].len > 0) {
            if ((size_t)lists[i].len > (SIZE_MAX - total_alloc) / sizeof(int)) {
                free(sorted_lists);
                return 0;
            }
            total_alloc += (size_t)lists[i].len * sizeof(int);
        }
    }

    if (total_alloc > 0 && total_alloc < 1024 * 1024) {
        bulk = malloc(total_alloc);
        if (bulk == NULL) {
            free(sorted_lists);
            return 0;
        }
        use_bulk = 1;
    } else {
        use_bulk = 0;
    }

    size_t offset = 0;
    for (int i = 0; i < count; i++) {
        sorted_lists[i].len = lists[i].len;
        if (lists[i].len > 0) {
            if (use_bulk) {
                sorted_lists[i].data = (int *)((char *)bulk + offset);
            } else {
                sorted_lists[i].data = (int *)malloc((size_t)lists[i].len * sizeof(int));
                if (sorted_lists[i].data == NULL) {
                    for (int j = 0; j < i; j++) {
                        if (lists[j].len > 0) {
                            free(sorted_lists[j].data);
                        }
                    }
                    free(bulk);
                    free(sorted_lists);
                    return 0;
                }
            }
            memcpy(sorted_lists[i].data, lists[i].data, (size_t)sorted_lists[i].len * sizeof(int));
            qsort(sorted_lists[i].data, (size_t)sorted_lists[i].len, sizeof(int), compare_ints);
            offset += (size_t)lists[i].len * sizeof(int);
        } else {
            sorted_lists[i].data = NULL;
        }
    }

    int unique_count = 0;
    int *is_unique = (int *)malloc((size_t)count * sizeof(int));
    if (is_unique == NULL) {
        if (use_bulk) {
            free(bulk);
        } else {
            for (int i = 0; i < count; i++) {
                if (sorted_lists[i].data != NULL) {
                    free(sorted_lists[i].data);
                }
            }
        }
        free(sorted_lists);
        return 0;
    }

    for (int i = 0; i < count; i++) {
        is_unique[i] = 1;
    }

    for (int i = 0; i < count; i++) {
        if (is_unique[i]) {
            unique_count++;
            for (int j = i + 1; j < count; j++) {
                if (is_unique[j] && list_equal(&sorted_lists[i], &sorted_lists[j])) {
                    is_unique[j] = 0;
                }
            }
        }
    }

    free(is_unique);
    if (use_bulk) {
        free(bulk);
    } else {
        for (int i = 0; i < count; i++) {
            if (sorted_lists[i].data != NULL) {
                free(sorted_lists[i].data);
            }
        }
    }
    free(sorted_lists);

    return unique_count;
}

int main(void) {
    int a1[] = {1, 2, 3};
    int a2[] = {3, 2, 1};
    int a3[] = {4, 5};
    int a4[] = {1, 2, 3, 4};
    int a5[] = {5, 4};
    int a6[] = {7};
    int a7[] = {7};

    List lists[] = {
        {a1, 3},
        {a2, 3},
        {a3, 2},
        {a4, 4},
        {a5, 2},
        {a6, 1},
        {a7, 1}
    };

    int num_lists = sizeof(lists) / sizeof(lists[0]);
    int unique = count_unique_lists(lists, num_lists);
    printf("%d\n", unique);

    return 0;
}