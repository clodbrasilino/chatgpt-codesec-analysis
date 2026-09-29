#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t length;
} List;

int* get_last_elements(List **sublists, size_t count) {
    if (sublists == NULL || count == 0) return NULL;

    int *result = (int *)malloc(count * sizeof(int));
    if (result == NULL) return NULL;

    for (size_t i = 0; i < count; ++i) {
        List *current = sublists[i];
        if (current != NULL && current->length > 0) {
            result[i] = current->data[current->length - 1];
        } else {
            result[i] = 0;
        }
    }

    return result;
}

int main() {
    int a1[] = {1, 2, 3};
    int a2[] = {4, 5, 6};
    int a3[] = {7, 8, 9};

    List list1 = {a1, 3};
    List list2 = {a2, 3};
    List list3 = {a3, 3};

    List *sublists[] = {&list1, &list2, &list3};
    size_t count = sizeof(sublists) / sizeof(sublists[0]);

    int *last_elements = get_last_elements(sublists, count);

    for (size_t i = 0; i < count; ++i) {
        printf("%d ", last_elements[i]);
    }
    printf("\n");

    free(last_elements);
    return 0;
}