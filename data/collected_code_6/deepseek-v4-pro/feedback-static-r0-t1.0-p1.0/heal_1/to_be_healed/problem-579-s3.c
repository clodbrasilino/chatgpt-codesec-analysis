#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int is_present(int *arr, int size, int value) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == value) {
            return 1;
        }
    }
    return 0;
}

int* find_dissimilar(int *tuple1, int size1, int *tuple2, int size2, int *result_size) {
    int *result = (int*)malloc((size1 + size2) * sizeof(int));
    if (result == NULL) {
        *result_size = 0;
        return NULL;
    }

    int count = 0;

    for (int i = 0; i < size1; i++) {
        if (!is_present(tuple2, size2, tuple1[i]) && !is_present(result, count, tuple1[i])) {
            result[count++] = tuple1[i];
        }
    }

    for (int i = 0; i < size2; i++) {
        if (!is_present(tuple1, size1, tuple2[i]) && !is_present(result, count, tuple2[i])) {
            result[count++] = tuple2[i];
        }
    }

    *result_size = count;
    return result;
}

int main() {
    int tuple1[] = {1, 2, 3, 4, 5};
    int tuple2[] = {4, 5, 6, 7, 8};
    int size1 = sizeof(tuple1) / sizeof(tuple1[0]);
    int size2 = sizeof(tuple2) / sizeof(tuple2[0]);
    int result_size = 0;

    int *dissimilar = find_dissimilar(tuple1, size1, tuple2, size2, &result_size);

    if (dissimilar == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Dissimilar elements: ");
    for (int i = 0; i < result_size; i++) {
        printf("%d ", dissimilar[i]);
    }
    printf("\n");

    free(dissimilar);
    return 0;
}