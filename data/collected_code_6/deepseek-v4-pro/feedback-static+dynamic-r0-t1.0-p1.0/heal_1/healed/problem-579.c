#include <stdio.h>
#include <stdlib.h>

int* find_dissimilar(const int tuple1[], int size1, const int tuple2[], int size2, int *result_size) {
    int *result = (int*)malloc((size1 + size2) * sizeof(int));
    if (result == NULL) {
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
            int duplicate = 0;
            for (int k = 0; k < count; k++) {
                if (result[k] == tuple1[i]) {
                    duplicate = 1;
                    break;
                }
            }
            if (!duplicate) {
                result[count++] = tuple1[i];
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
            int duplicate = 0;
            for (int k = 0; k < count; k++) {
                if (result[k] == tuple2[i]) {
                    duplicate = 1;
                    break;
                }
            }
            if (!duplicate) {
                result[count++] = tuple2[i];
            }
        }
    }
    
    *result_size = count;
    if (count == 0) {
        free(result);
        return NULL;
    }
    
    int *final_result = (int*)realloc(result, count * sizeof(int));
    if (final_result != NULL) {
        result = final_result;
    }
    
    return result;
}

int main() {
    int tuple1[] = {1, 2, 3, 4, 5};
    int tuple2[] = {4, 5, 6, 7, 8};
    int size1 = sizeof(tuple1) / sizeof(tuple1[0]);
    int size2 = sizeof(tuple2) / sizeof(tuple2[0]);
    int result_size;
    
    int *dissimilar = find_dissimilar(tuple1, size1, tuple2, size2, &result_size);
    
    if (dissimilar != NULL) {
        printf("Dissimilar elements: ");
        for (int i = 0; i < result_size; i++) {
            printf("%d ", dissimilar[i]);
        }
        printf("\n");
        free(dissimilar);
    } else {
        printf("No dissimilar elements found or memory allocation failed.\n");
    }
    
    return 0;
}