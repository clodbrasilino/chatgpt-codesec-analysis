#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 */
int *remove_negative(int *list, int size, int *new_size) {
    /* Possible weaknesses found:
     *  Assuming that condition 'new_size==NULL' is not redundant
     */
    if (list == NULL || size <= 0 || new_size == NULL) {
        /* Possible weaknesses found:
         *  Either the condition 'new_size==NULL' is redundant or there is possible null pointer dereference: new_size. [nullPointerRedundantCheck]
         *  Null pointer dereference
         */
        *new_size = 0;
        return NULL;
    }

    int *result = (int *)malloc(size * sizeof(int));
    if (result == NULL) {
        *new_size = 0;
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < size; i++) {
        if (list[i] >= 0) {
            result[count++] = list[i];
        }
    }

    if (count == 0) {
        free(result);
        *new_size = 0;
        return NULL;
    }

    int *final_result = (int *)realloc(result, count * sizeof(int));
    if (final_result == NULL) {
        free(result);
        *new_size = 0;
        return NULL;
    }

    *new_size = count;
    return final_result;
}

int main(void) {
    int test_list[] = {5, -3, 8, -1, 0, 7, -6, 4};
    int original_size = sizeof(test_list) / sizeof(test_list[0]);
    int new_size = 0;

    int *filtered = remove_negative(test_list, original_size, &new_size);

    if (filtered != NULL) {
        printf("Filtered list (%d elements): ", new_size);
        for (int i = 0; i < new_size; i++) {
            printf("%d ", filtered[i]);
        }
        printf("\n");
        free(filtered);
    } else {
        printf("No non-negative elements found or error occurred\n");
    }

    return 0;
}