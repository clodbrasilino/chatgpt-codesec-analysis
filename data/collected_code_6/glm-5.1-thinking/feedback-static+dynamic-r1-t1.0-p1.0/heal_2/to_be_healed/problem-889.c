#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t len;
} List;

typedef struct {
    List *lists;
    size_t len;
} ListOfLists;

void reverse_list(List *list) {
    if (list == NULL || list->data == NULL || list->len < 2) {
        return;
    }
    size_t left = 0;
    size_t right = list->len - 1;
    while (left < right) {
        int temp = list->data[left];
        list->data[left] = list->data[right];
        list->data[right] = temp;
        left++;
        right--;
    }
}

void reverse_each_list(ListOfLists *lol) {
    if (lol == NULL || lol->lists == NULL) {
        return;
    }
    for (size_t i = 0; i < lol->len; i++) {
        reverse_list(&lol->lists[i]);
    }
}

int main(void) {
    ListOfLists lol;
    lol.len = 3;
    lol.lists = malloc(lol.len * sizeof(List));
    if (lol.lists == NULL) {
        return EXIT_FAILURE;
    }

    const size_t lengths[] = {3, 2, 4};
    const int values[][4] = {{1, 2, 3}, {4, 5}, {6, 7, 8, 9}};

    for (size_t i = 0; i < lol.len; i++) {
        lol.lists[i].len = lengths[i];
        lol.lists[i].data = malloc(lengths[i] * sizeof(int));
        if (lol.lists[i].data == NULL && lengths[i] > 0) {
            for (size_t j = 0; j < i; j++) {
                free(lol.lists[j].data);
            }
            free(lol.lists);
            return EXIT_FAILURE;
        }
        size_t copy_size = lengths[i] * sizeof(int);
        if (copy_size <= sizeof(values[i])) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(lol.lists[i].data, values[i], copy_size);
        }
    }

    reverse_each_list(&lol);

    for (size_t i = 0; i < lol.len; i++) {
        for (size_t j = 0; j < lol.lists[i].len; j++) {
            printf("%d ", lol.lists[i].data[j]);
        }
        printf("\n");
    }

    for (size_t i = 0; i < lol.len; i++) {
        free(lol.lists[i].data);
    }
    free(lol.lists);

    return EXIT_SUCCESS;
}