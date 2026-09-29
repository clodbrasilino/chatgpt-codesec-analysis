#include <stdio.h>

int remove_negative_numbers(int *list, int size) {
    int insert = 0;
    int i;

    if (size < 0) {
        return -1;
    }

    if (list == NULL && size > 0) {
        return -1;
    }

    for (i = 0; i < size; ++i) {
        if (list[i] >= 0) {
            list[insert] = list[i];
            ++insert;
        }
    }

    return insert;
}

int main(void) {
    int list[] = {5, -3, 0, -8, 12, -1, 7};
    int size = (int)(sizeof(list) / sizeof(list[0]));
    int new_size;
    int i;

    new_size = remove_negative_numbers(list, size);

    if (new_size < 0) {
        printf("Error: invalid input\n");
        return 1;
    }

    for (i = 0; i < new_size; ++i) {
        printf("%d ", list[i]);
    }
    printf("\n");

    return 0;
}