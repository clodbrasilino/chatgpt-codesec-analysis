#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} IntList;

void remove_odd(IntList *list) {
    if (list == NULL || list->data == NULL) {
        return;
    }
    
    size_t new_size = 0;
    for (size_t i = 0; i < list->size; ++i) {
        if (list->data[i] % 2 == 0) {
            list->data[new_size++] = list->data[i];
        }
    }
    
    if (new_size == 0) {
        free(list->data);
        list->data = NULL;
    } else {
        int *temp = realloc(list->data, new_size * sizeof(int));
        if (temp != NULL) {
            list->data = temp;
        }
    }
    
    list->size = new_size;
}

int main(void) {
    IntList list;
    list.size = 6;
    list.data = malloc(list.size * sizeof(int));
    
    if (list.data == NULL) {
        return EXIT_FAILURE;
    }
    
    list.data[0] = 1;
    list.data[1] = 2;
    list.data[2] = 3;
    list.data[3] = 4;
    list.data[4] = 5;
    list.data[5] = 6;

    remove_odd(&list);

    for (size_t i = 0; i < list.size; ++i) {
        printf("%d ", list.data[i]);
    }
    printf("\n");

    free(list.data);

    return EXIT_SUCCESS;
}