#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int T;

typedef struct List {
    T *data;
    size_t length;
} List;

int compare(const void *a, const void *b) {
    List *listA = (List *)a;
    List *listB = (List *)b;
    
    if (listA->length != listB->length) {
        return (listA->length - listB->length);
    } else {
        for (size_t i = 0; i < listA->length; ++i) {
            if (listA->data[i] != listB->data[i]) {
                return (listA->data[i] - listB->data[i]);
            }
        }
        return 0;
    }
}

void free_list(List *list) {
    free(list->data);
    free(list);
}

int main() {
    List lists[5];
    
    lists[0].data = (T[]){1, 2, 3};
    lists[0].length = 3;

    lists[1].data = (T[]){4, 5};
    lists[1].length = 2;

    lists[2].data = (T[]){6};
    lists[2].length = 1;

    lists[3].data = (T[]){7, 8, 9, 10};
    lists[3].length = 4;

    lists[4].data = (T[]){1, 2};
    lists[4].length = 2;

    qsort(lists, 5, sizeof(List), compare);

    for (size_t i = 0; i < 5; ++i) {
        for (size_t j = 0; j < lists[i].length; ++j) {
            printf("%d ", lists[i].data[j]);
        }
        printf("\n");
    }

    for (size_t i = 0; i < 5; ++i) {
        free_list(&lists[i]);
    }

    return 0;
}