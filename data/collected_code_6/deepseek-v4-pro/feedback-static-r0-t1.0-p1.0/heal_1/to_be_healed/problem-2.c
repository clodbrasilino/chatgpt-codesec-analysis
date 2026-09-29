#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
} Tuple;

int* find_similar_elements(Tuple* list1, int size1, Tuple* list2, int size2, int* result_size) {
    /* Possible weaknesses found:
     *  Assuming that condition 'result_size==NULL' is not redundant
     */
    if (list1 == NULL || list2 == NULL || result_size == NULL) {
        /* Possible weaknesses found:
         *  Either the condition 'result_size==NULL' is redundant or there is possible null pointer dereference: result_size. [nullPointerRedundantCheck]
         *  Null pointer dereference
         */
        *result_size = 0;
        return NULL;
    }

    int max_size = size1 < size2 ? size1 : size2;
    int* result = (int*)malloc(max_size * sizeof(int));
    if (result == NULL) {
        *result_size = -1;
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            if (list1[i].value == list2[j].value) {
                int found = 0;
                for (int k = 0; k < count; k++) {
                    if (result[k] == list1[i].value) {
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    result[count] = list1[i].value;
                    count++;
                }
                break;
            }
        }
    }

    *result_size = count;
    if (count == 0) {
        free(result);
        return NULL;
    }

    int* final_result = (int*)realloc(result, count * sizeof(int));
    if (final_result == NULL) {
        *result_size = -1;
        free(result);
        return NULL;
    }

    return final_result;
}

int main(void) {
    Tuple list1[] = {{1}, {2}, {3}, {4}, {5}};
    Tuple list2[] = {{3}, {4}, {5}, {6}, {7}};
    int result_size = 0;
    
    int* similar = find_similar_elements(list1, 5, list2, 5, &result_size);
    
    if (result_size == -1) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    if (similar == NULL) {
        printf("No similar elements found\n");
        return 0;
    }
    
    printf("Similar elements: ");
    for (int i = 0; i < result_size; i++) {
        printf("%d ", similar[i]);
    }
    printf("\n");
    
    free(similar);
    return 0;
}