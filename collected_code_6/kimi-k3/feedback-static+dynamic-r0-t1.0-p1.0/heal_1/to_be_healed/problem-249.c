#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr1' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'arr2' can be declared as pointer to const [constParameterPointer]
 */
int* intersection(int* arr1, int size1, int* arr2, int size2, int* resultSize) {
    if (arr1 == NULL || arr2 == NULL || size1 < 0 || size2 < 0 || resultSize == NULL) {
        return NULL;
    }
    
    int maxSize = (size1 < size2) ? size1 : size2;
    int* result = (int*)malloc(maxSize * sizeof(int));
    
    if (result == NULL) {
        return NULL;
    }
    
    int count = 0;
    
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            if (arr1[i] == arr2[j]) {
                int isDuplicate = 0;
                for (int k = 0; k < count; k++) {
                    if (result[k] == arr1[i]) {
                        isDuplicate = 1;
                        break;
                    }
                }
                if (!isDuplicate) {
                    result[count] = arr1[i];
                    count++;
                }
                break;
            }
        }
    }
    
    *resultSize = count;
    return result;
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {3, 4, 5, 6, 7};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    int resultSize = 0;
    
    int* result = intersection(arr1, size1, arr2, size2, &resultSize);
    
    if (result != NULL) {
        printf("Intersection: ");
        for (int i = 0; i < resultSize; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    } else {
        printf("Error: Memory allocation failed or invalid input\n");
    }
    
    return 0;
}