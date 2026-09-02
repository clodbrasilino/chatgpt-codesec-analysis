#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int element;
    int count;
} ElementCount;

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
void findFrequency(int *arr, int n, ElementCount **result, int *size) {
    for (int i = 0; i < n; i++) {
        int isPresent = 0;
        for (int j = 0; j < *size; j++) {
            if ((*result)[j].element == arr[i]) {
                (*result)[j].count++;
                isPresent = 1;
                break;
            }
        }
        if (!isPresent) {
            *result = realloc(*result, (*size + 1) * sizeof(ElementCount));
            (*result)[*size].element = arr[i];
            (*result)[*size].count = 1;
            (*size)++;
        }
    }
}

int main() {
    int arr[] = {1, 2, 3, 2, 1, 3, 4, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    ElementCount *result = NULL;
    int size = 0;

    findFrequency(arr, n, &result, &size);

    for (int i = 0; i < size; i++) {
        printf("Element %d: %d times\n", result[i].element, result[i].count);
    }

    free(result);
    return 0;
}