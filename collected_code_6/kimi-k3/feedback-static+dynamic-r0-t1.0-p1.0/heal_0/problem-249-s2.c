#include <stdio.h>
#include <stdlib.h>

int* findIntersection(int* arr1, int size1, int* arr2, int size2, int* resultSize) {
    if (arr1 == NULL || arr2 == NULL || resultSize == NULL || size1 < 0 || size2 < 0) {
        if (resultSize != NULL) {
            *resultSize = 0;
        }
        return NULL;
    }

    if (size1 == 0 || size2 == 0) {
        *resultSize = 0;
        return NULL;
    }

    int maxSize = size1 < size2 ? size1 : size2;
    int* result = (int*)malloc(maxSize * sizeof(int));
    if (result == NULL) {
        *resultSize = 0;
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < size1; i++) {
        int found = 0;
        for (int j = 0; j < count; j++) {
            if (result[j] == arr1[i]) {
                found = 1;
                break;
            }
        }
        if (found) {
            continue;
        }
        for (int j = 0; j < size2; j++) {
            if (arr1[i] == arr2[j]) {
                result[count] = arr1[i];
                count++;
                break;
            }
        }
    }

    if (count == 0) {
        free(result);
        result = NULL;
    } else {
        int* temp = (int*)realloc(result, count * sizeof(int));
        if (temp != NULL) {
            result = temp;
        }
    }

    *resultSize = count;
    return result;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5, 3, 2};
    int arr2[] = {3, 4, 5, 6, 7, 3};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    int resultSize = 0;

    int* intersection = findIntersection(arr1, size1, arr2, size2, &resultSize);

    if (intersection != NULL && resultSize > 0) {
        printf("Intersection: ");
        for (int i = 0; i < resultSize; i++) {
            printf("%d ", intersection[i]);
        }
        printf("\n");
        free(intersection);
    } else {
        printf("No intersection found.\n");
    }

    return 0;
}