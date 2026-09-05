#include <stdio.h>
#include <stdlib.h>

void rotate_left(int *list, size_t size, size_t items) {
    if (size == 0) {
        return;
    }
    items = items % size;
    if (items == 0) {
        return;
    }
    int *temp = (int *)malloc(items * sizeof(int));
    if (temp == NULL) {
        return;
    }
    for (size_t i = 0; i < items; i++) {
        temp[i] = list[i];
    }
    for (size_t i = 0; i < size - items; i++) {
        list[i] = list[i + items];
    }
    for (size_t i = 0; i < items; i++) {
        list[size - items + i] = temp[i];
    }
    free(temp);
}

int main(void) {
    int list[] = {1, 2, 3, 4, 5, 6, 7};
    size_t size = sizeof(list) / sizeof(list[0]);
    size_t items = 3;
    rotate_left(list, size, items);
    for (size_t i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
    return 0;
}