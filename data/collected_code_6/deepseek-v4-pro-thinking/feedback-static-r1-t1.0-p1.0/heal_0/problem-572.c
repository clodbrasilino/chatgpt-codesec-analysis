#include <stdio.h>
#include <stdlib.h>

static int contains_value(const int *array, int size, int value) {
    for (int i = 0; i < size; i++) {
        if (array[i] == value) {
            return 1;
        }
    }
    return 0;
}

static int remove_duplicate_numbers_from_list(int *list, int size) {
    if (size < 0) {
        return -1;
    }
    if (size == 0) {
        return 0;
    }
    if (list == NULL) {
        return -1;
    }
    if ((size_t)size > ((size_t)-1) / sizeof(int)) {
        return -1;
    }

    int *temp = malloc((size_t)size * sizeof(int));
    if (temp == NULL) {
        return -1;
    }

    int unique_count = 0;
    for (int i = 0; i < size; i++) {
        if (!contains_value(temp, unique_count, list[i])) {
            temp[unique_count] = list[i];
            unique_count++;
        }
    }

    for (int i = 0; i < unique_count; i++) {
        list[i] = temp[i];
    }

    free(temp);
    return unique_count;
}

int remove_duplicate_numbers(int **lists, int *sizes, int list_count) {
    if (list_count < 0) {
        return -1;
    }
    if (list_count == 0) {
        return 0;
    }
    if (lists == NULL || sizes == NULL) {
        return -1;
    }

    for (int i = 0; i < list_count; i++) {
        int new_size = remove_duplicate_numbers_from_list(lists[i], sizes[i]);
        if (new_size < 0) {
            return -1;
        }
        sizes[i] = new_size;
    }

    return 0;
}

int main(void) {
    int list1[] = {1, 2, 3, 2, 4, 3};
    int list2[] = {5, 6, 5, 7, 6, 8, 5};
    int sizes[] = {6, 7};
    int *lists[] = {list1, list2};

    if (remove_duplicate_numbers(lists, sizes, 2) != 0) {
        return 1;
    }

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < sizes[i]; j++) {
            printf("%d ", lists[i][j]);
        }
        printf("\n");
    }

    return 0;
}