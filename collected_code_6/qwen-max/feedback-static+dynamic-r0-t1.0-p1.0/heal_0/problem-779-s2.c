#include <stdio.h>
#include <stdlib.h>

#define MAX_LISTS 100
#define MAX_LIST_SIZE 10

typedef struct {
    int data[MAX_LIST_SIZE];
    int size;
} IntList;

int compare_lists(IntList *a, IntList *b) {
    if (a->size != b->size) return 0;
    for (int i = 0; i < a->size; i++) {
        if (a->data[i] != b->data[i]) return 0;
    }
    return 1;
}

int is_unique(IntList **lists, int list_count, IntList *new_list) {
    for (int i = 0; i < list_count; i++) {
        if (compare_lists(lists[i], new_list)) return 0;
    }
    return 1;
}

int count_unique_lists(IntList **lists, int list_count) {
    int count = 0;
    IntList *unique_lists[MAX_LISTS] = {0};
    for (int i = 0; i < list_count; i++) {
        if (is_unique(unique_lists, count, lists[i])) {
            unique_lists[count++] = lists[i];
        }
    }
    return count;
}

int main() {
    IntList lists[] = {
        {{1, 2, 3}, 3},
        {{4, 5}, 2},
        {{1, 2, 3}, 3},
        {{6, 7, 8, 9}, 4},
        {{1, 2, 3, 4}, 4},
    };
    int list_count = sizeof(lists) / sizeof(lists[0]);
    
    int unique_count = count_unique_lists((IntList **)lists, list_count);
    printf("Number of unique lists: %d\n", unique_count);

    return 0;
}