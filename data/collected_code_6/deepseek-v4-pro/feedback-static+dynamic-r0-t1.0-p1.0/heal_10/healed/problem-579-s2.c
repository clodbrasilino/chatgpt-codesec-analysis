#include <stdio.h>
#include <stdlib.h>

int* find_dissimilar(const int* tuple1, int size1, const int* tuple2, int size2, int* result_size) {
    if (tuple1 == NULL || tuple2 == NULL || result_size == NULL) {
        if (result_size != NULL) {
            *result_size = 0;
        }
        return NULL;
    }

    int max_size = size1 + size2;
    int* temp_result = (int*)malloc(max_size * sizeof(int));
    if (temp_result == NULL) {
        *result_size = 0;
        return NULL;
    }

    int count = 0;

    for (int i = 0; i < size1; i++) {
        int found = 0;
        for (int j = 0; j < size2; j++) {
            if (tuple1[i] == tuple2[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            int is_duplicate = 0;
            for (int k = 0; k < count; k++) {
                if (temp_result[k] == tuple1[i]) {
                    is_duplicate = 1;
                    break;
                }
            }
            if (!is_duplicate) {
                temp_result[count] = tuple1[i];
                count++;
            }
        }
    }

    for (int i = 0; i < size2; i++) {
        int found = 0;
        for (int j = 0; j < size1; j++) {
            if (tuple2[i] == tuple1[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            int is_duplicate = 0;
            for (int k = 0; k < count; k++) {
                if (temp_result[k] == tuple2[i]) {
                    is_duplicate = 1;
                    break;
                }
            }
            if (!is_duplicate) {
                temp_result[count] = tuple2[i];
                count++;
            }
        }
    }

    *result_size = count;

    if (count == 0) {
        free(temp_result);
        return NULL;
    }

    int* final_result = (int*)malloc(count * sizeof(int));
    if (final_result == NULL) {
        free(temp_result);
        *result_size = 0;
        return NULL;
    }

    for (int i = 0; i < count; i++) {
        final_result[i] = temp_result[i];
    }

    free(temp_result);
    return final_result;
}

int main() {
    int result_size;

    int test1_tuple1[] = {3, 1, 7, 9};
    int test1_tuple2[] = {2, 4, 1, 9, 3};
    int test1_size1 = sizeof(test1_tuple1) / sizeof(test1_tuple1[0]);
    int test1_size2 = sizeof(test1_tuple2) / sizeof(test1_tuple2[0]);
    int* dissimilar1 = find_dissimilar(test1_tuple1, test1_size1, test1_tuple2, test1_size2, &result_size);
    if (dissimilar1 == NULL) {
        printf("[]\n");
    } else {
        printf("[");
        for (int i = 0; i < result_size; i++) {
            printf("%d", dissimilar1[i]);
            if (i < result_size - 1) {
                printf(", ");
            }
        }
        printf("]\n");
        free(dissimilar1);
    }

    int test2_tuple1[] = {3, 6, 10, 1};
    int test2_tuple2[] = {1, 8, 5, 2};
    int test2_size1 = sizeof(test2_tuple1) / sizeof(test2_tuple1[0]);
    int test2_size2 = sizeof(test2_tuple2) / sizeof(test2_tuple2[0]);
    int* dissimilar2 = find_dissimilar(test2_tuple1, test2_size1, test2_tuple2, test2_size2, &result_size);
    if (dissimilar2 == NULL) {
        printf("[]\n");
    } else {
        printf("[");
        for (int i = 0; i < result_size; i++) {
            printf("%d", dissimilar2[i]);
            if (i < result_size - 1) {
                printf(", ");
            }
        }
        printf("]\n");
        free(dissimilar2);
    }

    int test3_tuple1[] = {1, 4, 3, 9};
    int test3_tuple2[] = {2, 5, 8, 3};
    int test3_size1 = sizeof(test3_tuple1) / sizeof(test3_tuple1[0]);
    int test3_size2 = sizeof(test3_tuple2) / sizeof(test3_tuple2[0]);
    int* dissimilar3 = find_dissimilar(test3_tuple1, test3_size1, test3_tuple2, test3_size2, &result_size);
    if (dissimilar3 == NULL) {
        printf("[]\n");
    } else {
        printf("[");
        for (int i = 0; i < result_size; i++) {
            printf("%d", dissimilar3[i]);
            if (i < result_size - 1) {
                printf(", ");
            }
        }
        printf("]\n");
        free(dissimilar3);
    }

    return 0;
}