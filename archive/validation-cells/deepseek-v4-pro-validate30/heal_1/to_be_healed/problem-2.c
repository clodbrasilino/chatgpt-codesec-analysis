#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int* findSimilarElements(Tuple* list1, int size1, Tuple* list2, int size2, int* resultSize) {
    /* Possible weaknesses found:
     *  Assuming that condition 'resultSize==NULL' is not redundant
     */
    if (list1 == NULL || list2 == NULL || resultSize == NULL || size1 < 0 || size2 < 0) {
        /* Possible weaknesses found:
         *  Null pointer dereference
         *  Either the condition 'resultSize==NULL' is redundant or there is possible null pointer dereference: resultSize. [nullPointerRedundantCheck]
         */
        *resultSize = 0;
        return NULL;
    }

    int maxSize = size1 > size2 ? size1 : size2;
    int* result = (int*)malloc(maxSize * sizeof(int));
    
    if (result == NULL) {
        *resultSize = 0;
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            if (list1[i].first == list2[j].first && list1[i].second == list2[j].second) {
                result[count++] = list1[i].first;
                result[count++] = list1[i].second;
                break;
            }
        }
    }

    *resultSize = count;
    return result;
}

int main(void) {
    Tuple list1[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
    Tuple list2[] = {{3, 4}, {9, 10}, {5, 6}, {11, 12}};
    
    int resultSize = 0;
    int* similar = findSimilarElements(list1, 4, list2, 4, &resultSize);
    
    if (similar == NULL) {
        printf("No similar elements found or error occurred\n");
        return 1;
    }
    
    printf("Similar elements: ");
    for (int i = 0; i < resultSize; i += 2) {
        printf("(%d, %d) ", similar[i], similar[i + 1]);
    }
    printf("\n");
    
    free(similar);
    return 0;
}