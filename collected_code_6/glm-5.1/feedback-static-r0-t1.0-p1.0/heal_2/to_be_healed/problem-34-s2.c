#include <stdio.h>
#include <stdlib.h>

int find_missing(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return -1;
    }
    
    size_t low = 0;
    size_t high = size - 1;
    
    while (low <= high) {
        size_t mid = low + (high - low) / 2;
        
        if ((size_t)arr[mid] == mid + (size_t)arr[0]) {
            low = mid + 1;
        } else {
            if (mid == 0) {
                break;
            }
            high = mid - 1;
        }
    }
    
    return (int)((size_t)arr[0] + low);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    /* Possible weaknesses found:
     *  Assuming that condition 'argc<2' is not redundant
     */
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <sorted_integers...>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     *  Assignment 'size=(unsigned long)(argc-1)', assigned value is greater than 0
     */
    size_t size = (size_t)(argc - 1);
    /* Possible weaknesses found:
     *  Condition 'size==0' is always false [knownConditionTrueFalse]
     *  Condition 'size==0' is always false
     */
    if (size == 0) {
        return EXIT_SUCCESS;
    }

    int *arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    for (size_t i = 0; i < size; i++) {
        arr[i] = atoi(argv[i + 1]);
    }
    
    int missing = find_missing(arr, size);
    printf("%d\n", missing);
    
    free(arr);
    return EXIT_SUCCESS;
}