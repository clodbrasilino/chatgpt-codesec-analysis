#include <stdio.h>
#include <stddef.h>

void interchange_first_last(int *list, size_t size) {
    if (list == NULL || size < 2) {
        return;
    }

    int temp = list[0];
    list[0] = list[size - 1];
    list[size - 1] = temp;
}

int main(void) {
    int list[] = {10, 20, 30, 40, 50};
    size_t size = sizeof(list) / sizeof(list[0]);

    interchange_first_last(list, size);

    for (size_t i = 0; i < size; ++i) {
        printf("%d ", list[i]);
    }
    printf("\n");

    return 0;
}