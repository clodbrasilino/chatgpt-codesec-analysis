#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int *elements;
    int size;
} List;

void remove_duplicates(List *list) {
    if (list->size <= 1) return;

    int *new_elements = (int *)malloc(list->size * sizeof(int));
    if (new_elements == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    int new_size = 0;
    for (int i = 0; i < list->size; ++i) {
        int is_duplicate = 0;
        for (int j = 0; j < new_size; ++j) {
            if (list->elements[i] == new_elements[j]) {
                is_duplicate = 1;
                break;
            }
        }
        if (!is_duplicate) {
            new_elements[new_size++] = list->elements[i];
        }
    }

    /* Possible weaknesses found:
     * ASan: attempting
     */
    free(list->elements);
    list->elements = new_elements;
    list->size = new_size;
}

int main() {
    List list = { .elements = (int[]){1, 2, 2, 3, 4, 4, 5}, .size = 7 };

    remove_duplicates(&list);

    for (int i = 0; i < list.size; ++i) {
        printf("%d ", list.elements[i]);
    }
    printf("\n");

    free(list.elements);
    return 0;
}