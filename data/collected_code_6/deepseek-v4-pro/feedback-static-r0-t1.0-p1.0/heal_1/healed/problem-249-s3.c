#include <stdio.h>
#include <stdlib.h>

int* intersection(const int* arr1, int size1, const int* arr2, int size2, int* result_size) {
    if (arr1 == NULL || arr2 == NULL || result_size == NULL || size1 <= 0 || size2 <= 0) {
        *result_size = 0;
        return NULL;
    }

    int max_size = size1 < size2 ? size1 : size2;
    int* result = (int*)malloc((size_t)max_size * sizeof(int));
    int* temp = (int*)malloc((size_t)max_size * sizeof(int));
    
    if (result == NULL || temp == NULL) {
        free(result);
        free(temp);
        *result_size = 0;
        return NULL;
    }

    int count = 0;
    int temp_count = 0;

    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            if (arr1[i] == arr2[j]) {
                int found = 0;
                for (int k = 0; k < temp_count; k++) {
                    if (temp[k] == arr1[i]) {
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    temp[temp_count++] = arr1[i];
                    result[count++] = arr1[i];
                }
                break;
            }
        }
    }

    free(temp);
    *result_size = count;

    if (count == 0) {
        free(result);
        return NULL;
    }

    int* final_result = (int*)malloc((size_t)count * sizeof(int));
    if (final_result == NULL) {
        free(result);
        *result_size = 0;
        return NULL;
    }

    for (int i = 0; i < count; i++) {
        final_result[i] = result[i];
    }

    free(result);
    *result_size = count;
    return final_result;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5, 6};
    int arr2[] = {4, 5, 6, 7, 8, 9};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    int result_size = 0;

    int* result = intersection(arr1, size1, arr2, size2, &result_size);

    if (result != NULL) {
        printf("Intersection: ");
        for (int i = 0; i < result_size; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    } else {
        printf("No intersection found or error occurred.\n");
    }

    int arr3[] = {1, 2, 3};
    int arr4[] = {4, 5, 6};
    size1 = sizeof(arr3) / sizeof(arr3[0]);
    size2 = sizeof(arr4) / sizeof(arr4[0]);
    result_size = 0;

    result = intersection(arr3, size1, arr4, size2, &result_size);

    if (result != NULL) {
        printf("Intersection: ");
        for (int i = 0; i < result_size; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    } else {
        printf("No intersection found or error occurred.\n");
    }

    int arr5[] = {1, 2, 3, 4};
    int arr6[] = {3, 4, 5, 6, 3};
    size1 = sizeof(arr5) / sizeof(arr5[0]);
    size2 = sizeof(arr6) / sizeof(arr6[0]);
    result_size = 0;

    result = intersection(arr5, size1, arr6, size2, &result_size);

    if (result != NULL) {
        printf("Intersection: ");
        for (int i = 0; i < result_size; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    } else {
        printf("No intersection found or error occurred.\n");
    }

    return 0;
}