#include <stdio.h>
#include <stdlib.h>

struct Pair {
    int first;
    int second;
};

/* Possible weaknesses found:
 *  Parameter 'arr1' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'arr2' can be declared as pointer to const [constParameterPointer]
 */
void findPairs(int* arr1, int size1, int* arr2, int size2, int k, struct Pair* result, int* resultSize) {
    *resultSize = 0;
    
    if (arr1 == NULL || arr2 == NULL || result == NULL || k <= 0 || size1 <= 0 || size2 <= 0) {
        return;
    }

    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            if (*resultSize < k) {
                result[*resultSize].first = arr1[i];
                result[*resultSize].second = arr2[j];
                (*resultSize)++;
            } else {
                return;
            }
        }
    }
}

int main() {
    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5, 6};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    /* Possible weaknesses found:
     *  Assignment 'k=4', assigned value is 4
     */
    int k = 4;
    int resultSize = 0;
    
    /* Possible weaknesses found:
     *  Condition 'k>0' is always true
     *  Condition 'k>0' is always true [knownConditionTrueFalse]
     */
    if (k > 0) {
        struct Pair* result = (struct Pair*)malloc(k * sizeof(struct Pair));
        if (result != NULL) {
            findPairs(arr1, size1, arr2, size2, k, result, &resultSize);
            
            for (int i = 0; i < resultSize; i++) {
                printf("(%d, %d)\n", result[i].first, result[i].second);
            }
            
            free(result);
        }
    }
    
    return 0;
}