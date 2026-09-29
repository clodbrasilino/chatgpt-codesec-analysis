#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int sumNonRepeated(int *arr, int size) {
    if (arr == NULL || size <= 0) {
        return 0;
    }
    
    int sum = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'count' can be reduced. [variableScope]
     */
    int count;
    
    for (int i = 0; i < size; i++) {
        count = 0;
        for (int j = 0; j < size; j++) {
            if (arr[i] == arr[j]) {
                count++;
            }
        }
        if (count == 1) {
            sum += arr[i];
        }
    }
    
    return sum;
}

int main(void) {
    int arr[] = {1, 2, 3, 2, 1, 4, 5};
    /* Possible weaknesses found:
     *  Assignment 'size=sizeof(arr)/sizeof(arr[0])', assigned value is 7
     */
    int size = sizeof(arr) / sizeof(arr[0]);
    
    /* Possible weaknesses found:
     *  Condition 'size==0' is always false [knownConditionTrueFalse]
     *  Condition 'size==0' is always false
     */
    if (size == 0) {
        fprintf(stderr, "Array is empty\n");
        return EXIT_FAILURE;
    }
    
    int result = sumNonRepeated(arr, size);
    printf("Sum of non-repeated elements: %d\n", result);
    
    return EXIT_SUCCESS;
}