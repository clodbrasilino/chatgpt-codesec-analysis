#include <stdio.h>
#include <stdlib.h>

void remove_odd_numbers(int **list, size_t *size) {
    if (list == NULL || *list == NULL || size == NULL) {
        return;
    }

    size_t new_size = 0;
    for (size_t i = 0; i < *size; ++i) {
        if ((*list)[i] % 2 == 0) {
            new_size++;
        }
    }

    if (new_size == 0) {
        free(*list);
        *list = NULL;
        *size = 0;
        return;
    }

    int *new_list = (int *)malloc(new_size * sizeof(int));
    if (new_list == NULL) {
        return;
    }

    size_t index = 0;
    for (size_t i = 0; i < *size; ++i) {
        if ((*list)[i] % 2 == 0) {
            new_list[index++] = (*list)[i];
        }
    }

    free(*list);
    *list = new_list;
    *size = new_size;
}

int main(void) {
    size_t size = 5;
    int *list = (int *)malloc(size * sizeof(int));
    if (list == NULL) {
        return 1;
    }

    list[0] = 1;
    list[1] = 2;
    list[2] = 3;
    list[3] = 4;
    list[4] = 5;

    remove_odd_numbers(&list, &size);

    if (list != NULL) {
        for (size_t i = 0; i < size; ++i) {
            printf("%d ", list[i]);
        }
        printf("\n");
        free(list);
    }

    return 0;
}