#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct List {
    int *data;
    size_t size;
} List;

int compare_lists(const void *a, const void *b) {
    List *list1 = (List *)a;
    List *list2 = (List *)b;
    if (list1->size != list2->size) return 0;
    return memcmp(list1->data, list2->data, list1->size * sizeof(int)) == 0;
}

int count_unique_lists(List *lists, size_t n) {
    int unique_count = 0;
    for (size_t i = 0; i < n; ++i) {
        int is_unique = 1;
        for (size_t j = 0; j < i; ++j) {
            if (compare_lists(&lists[i], &lists[j])) {
                is_unique = 0;
                break;
            }
        }
        if (is_unique) unique_count++;
    }
    return unique_count;
}

int main() {
    List lists[] = {
        { .data = (int[]){1, 2, 3}, .size = 3 },
        { .data = (int[]){4, 5, 6}, .size = 3 },
        { .data = (int[]){1, 2, 3}, .size = 3 },
        { .data = (int[]){7, 8, 9}, .size = 3 },
        { .data = (int[]){4, 5, 6}, .size = 3 }
    };
    size_t n = sizeof(lists) / sizeof(lists[0]);
    int unique_count = count_unique_lists(lists, n);
    printf("Number of unique lists: %d\n", unique_count);
    return 0;
}