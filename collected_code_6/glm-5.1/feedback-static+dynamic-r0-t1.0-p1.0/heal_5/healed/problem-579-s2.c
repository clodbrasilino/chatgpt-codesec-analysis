#include <stdio.h>
#include <stdlib.h>

int* find_dissimilar(const int* tuple1, size_t size1, const int* tuple2, size_t size2, size_t* result_size) {
    size_t max_capacity = size1 + size2;
    *result_size = 0;
    if (max_capacity == 0) {
        return NULL;
    }
    int* temp_result = (int*)malloc(max_capacity * sizeof(int));
    if (temp_result == NULL) {
        return NULL;
    }

    size_t count = 0;

    for (size_t i = 0; i < size1; i++) {
        int found = 0;
        for (size_t j = 0; j < size2; j++) {
            if (tuple1[i] == tuple2[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            temp_result[count++] = tuple1[i];
        }
    }

    for (size_t i = 0; i < size2; i++) {
        int found = 0;
        for (size_t j = 0; j < size1; j++) {
            if (tuple2[i] == tuple1[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            temp_result[count++] = tuple2[i];
        }
    }

    int* final_result = NULL;
    if (count > 0) {
        final_result = (int*)realloc(temp_result, count * sizeof(int));
        if (final_result == NULL) {
            *result_size = count;
            return temp_result;
        }
    } else {
        free(temp_result);
    }

    *result_size = count;
    return final_result;
}

int main() {
    int t1[] = {3, 6, 7, 10};
    int t2[] = {2, 6, 7, 8};
    size_t s1 = sizeof(t1) / sizeof(t1[0]);
    size_t s2 = sizeof(t2) / sizeof(t2[0]);
    size_t res_size = 0;

    int* dissimilar = find_dissimilar(t1, s1, t2, s2, &res_size);

    printf("[");
    for (size_t i = 0; i < res_size; i++) {
        printf("%d", dissimilar[i]);
        if (i < res_size - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    free(dissimilar);

    return 0;
}