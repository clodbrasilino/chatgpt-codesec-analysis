#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'tuple2' can be declared as const array [constParameter]
 *  Parameter 'tuple1' can be declared as const array [constParameter]
 */
int* find_dissimilar(int tuple1[], int size1, int tuple2[], int size2, int *result_size) {
    int *result = (int*)malloc((size1 + size2) * sizeof(int));
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
    return result;
}

int main() {
    int tuple1[] = {1, 2, 3, 4, 5};
    int tuple2[] = {4, 5, 6, 7, 8};
    int size1 = sizeof(tuple1) / sizeof(tuple1[0]);
    int size2 = sizeof(tuple2) / sizeof(tuple2[0]);
    int result_size;
    
    int *dissimilar = find_dissimilar(tuple1, size1, tuple2, size2, &result_size);
    
    printf("Dissimilar elements: ");
    for (int i = 0; i < result_size; i++) {
        printf("%d ", dissimilar[i]);
    }
    printf("\n");
    
    free(dissimilar);
    return 0;
}