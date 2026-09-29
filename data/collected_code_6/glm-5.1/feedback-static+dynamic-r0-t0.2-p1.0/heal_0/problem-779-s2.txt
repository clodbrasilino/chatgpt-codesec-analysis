#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t len;
} List;

int compare_lists(const void *a, const void *b) {
    const List *la = (const List *)a;
    const List *lb = (const List *)b;
    
    if (la->len != lb->len) {
        return (la->len > lb->len) - (la->len < lb->len);
    }
    
    for (size_t i = 0; i < la->len; i++) {
        if (la->data[i] != lb->data[i]) {
            return (la->data[i] > lb->data[i]) - (la->data[i] < lb->data[i]);
        }
    }
    
    return 0;
}

size_t count_unique_lists(List *lists, size_t count) {
    if (lists == NULL || count == 0) {
        return 0;
    }
    
    qsort(lists, count, sizeof(List), compare_lists);
    
    size_t unique_count = 1;
    for (size_t i = 1; i < count; i++) {
        if (compare_lists(&lists[i - 1], &lists[i]) != 0) {
            unique_count++;
        }
    }
    
    return unique_count;
}

int main(void) {
    int d1[] = {1, 2, 3};
    int d2[] = {4, 5};
    int d3[] = {1, 2, 3};
    int d4[] = {7};
    int d5[] = {4, 5};
    
    List lists[] = {
        {d1, 3},
        {d2, 2},
        {d3, 3},
        {d4, 1},
        {d5, 2}
    };
    
    size_t num_lists = sizeof(lists) / sizeof(lists[0]);
    size_t unique = count_unique_lists(lists, num_lists);
    
    printf("%zu\n", unique);
    
    return 0;
}