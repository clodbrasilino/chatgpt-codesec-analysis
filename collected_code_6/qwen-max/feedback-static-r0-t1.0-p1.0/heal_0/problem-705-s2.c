#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int T;

typedef struct {
    T *array;
    size_t used;
    size_t size;
} List;

void init_list(List *list, size_t initial_size) {
    list->array = (T *)malloc(initial_size * sizeof(T));
    list->used = 0;
    list->size = initial_size;
}

void free_list(List *list) {
    free(list->array);
    list->array = NULL;
    list->used = 0;
    list->size = 0;
}

int compare_lists(const void *a, const void *b) {
    List *list1 = (List *)a;
    List *list2 = (List *)b;
    
    if (list1->used != list2->used) {
        return (list1->used - list2->used);
    }
    
    for (size_t i = 0; i < list1->used; ++i) {
        if (list1->array[i] != list2->array[i]) {
            return (list1->array[i] - list2->array[i]);
        }
    }
    
    return 0;
}

void sort_lists(List *lists, size_t count) {
    qsort(lists, count, sizeof(List), compare_lists);
}

int main() {
    List lists[3];
    init_list(&lists[0], 5);
    init_list(&lists[1], 3);
    init_list(&lists[2], 4);
    
    lists[0].array[0] = 1;
    lists[0].array[1] = 2;
    lists[0].array[2] = 3;
    lists[0].used = 3;
    
    lists[1].array[0] = 1;
    lists[1].array[1] = 2;
    lists[1].used = 2;
    
    lists[2].array[0] = 1;
    lists[2].array[1] = 2;
    lists[2].array[2] = 3;
    lists[2].array[3] = 4;
    lists[2].used = 4;
    
    sort_lists(lists, 3);
    
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < lists[i].used; ++j) {
            printf("%d ", lists[i].array[j]);
        }
        printf("\n");
    }
    
    for (size_t i = 0; i < 3; ++i) {
        free_list(&lists[i]);
    }
    
    return 0;
}