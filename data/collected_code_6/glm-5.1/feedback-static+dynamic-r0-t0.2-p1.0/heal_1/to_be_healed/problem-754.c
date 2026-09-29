#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'b' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'c' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'a' can be declared as pointer to const [constParameterPointer]
 */
int* find_common_index_elements(int* a, int* b, int* c, int size, int* result_size) {
    if (a == NULL || b == NULL || c == NULL || size <= 0 || result_size == NULL) {
        if (result_size != NULL) {
            *result_size = 0;
        }
        return NULL;
    }

    int* result = (int*)malloc(size * sizeof(int));
    if (result == NULL) {
        *result_size = 0;
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < size; i++) {
        if (a[i] == b[i] && b[i] == c[i]) {
            result[count] = i;
            count++;
        }
    }

    if (count == 0) {
        free(result);
        *result_size = 0;
        return NULL;
    }

    int* final_result = (int*)realloc(result, count * sizeof(int));
    if (final_result == NULL) {
        *result_size = count;
        return result;
    }

    *result_size = count;
    return final_result;
}

int main(void) {
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {1, 2, 9, 4, 8};
    int c[] = {1, 7, 3, 4, 6};
    int size = sizeof(a) / sizeof(a[0]);
    int result_size = 0;

    int* common_indices = find_common_index_elements(a, b, c, size, &result_size);

    if (common_indices != NULL) {
        for (int i = 0; i < result_size; i++) {
            printf("%d ", common_indices[i]);
        }
        printf("\n");
        free(common_indices);
    }

    return 0;
}