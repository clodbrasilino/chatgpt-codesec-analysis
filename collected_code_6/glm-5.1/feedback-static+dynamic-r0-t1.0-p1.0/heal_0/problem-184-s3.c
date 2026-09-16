#include <stdio.h>
#include <stdlib.h>

int* find_greater(const int* list, size_t size, int specified, size_t* result_size) {
    if (list == NULL || result_size == NULL) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < size; i++) {
        if (list[i] > specified) {
            count++;
        }
    }

    *result_size = count;
    if (count == 0) {
        return NULL;
    }

    int* result = (int*)malloc(count * sizeof(int));
    if (result == NULL) {
        *result_size = 0;
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < size; i++) {
        if (list[i] > specified) {
            result[j] = list[i];
            j++;
        }
    }

    return result;
}

int main(void) {
    int list[] = {1, 5, 8, 12, 3, 9, 7};
    size_t size = sizeof(list) / sizeof(list[0]);
    int specified = 6;
    size_t result_size = 0;

    int* result = find_greater(list, size, specified, &result_size);

    if (result != NULL) {
        for (size_t i = 0; i < result_size; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    } else {
        printf("No values greater than %d found.\n", specified);
    }

    return 0;
}