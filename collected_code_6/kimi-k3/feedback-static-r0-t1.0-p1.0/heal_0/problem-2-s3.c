#include <stdio.h>
#include <stdlib.h>

#define TUPLE_SIZE 2

typedef struct {
    int first;
    int second;
} Tuple;

Tuple* findSimilarElements(const Tuple* list1, size_t size1, const Tuple* list2, size_t size2, size_t* resultSize) {
    if (list1 == NULL || list2 == NULL || resultSize == NULL || size1 == 0 || size2 == 0) {
        if (resultSize != NULL) {
            *resultSize = 0;
        }
        return NULL;
    }
    
    size_t capacity = (size1 < size2) ? size1 : size2;
    Tuple* result = (Tuple*)malloc(capacity * sizeof(Tuple));
    if (result == NULL) {
        *resultSize = 0;
        return NULL;
    }
    
    size_t count = 0;
    
    for (size_t i = 0; i < size1; i++) {
        for (size_t j = 0; j < size2; j++) {
            if (list1[i].first == list2[j].first && list1[i].second == list2[j].second) {
                if (count < capacity) {
                    result[count].first = list1[i].first;
                    result[count].second = list1[i].second;
                    count++;
                }
                break;
            }
        }
    }
    
    if (count == 0) {
        free(result);
        *resultSize = 0;
        return NULL;
    }
    
    Tuple* trimmed = (Tuple*)realloc(result, count * sizeof(Tuple));
    if (trimmed != NULL) {
        result = trimmed;
    }
    
    *resultSize = count;
    return result;
}

void printTuples(const Tuple* tuples, size_t size) {
    if (tuples == NULL) {
        printf("No similar elements found.\n");
        return;
    }
    
    printf("Similar elements: ");
    for (size_t i = 0; i < size; i++) {
        printf("(%d, %d) ", tuples[i].first, tuples[i].second);
    }
    printf("\n");
}

int main(void) {
    Tuple list1[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
    Tuple list2[] = {{3, 4}, {7, 8}, {9, 10}, {11, 12}};
    
    size_t size1 = sizeof(list1) / sizeof(list1[0]);
    size_t size2 = sizeof(list2) / sizeof(list2[0]);
    size_t resultSize = 0;
    
    Tuple* similar = findSimilarElements(list1, size1, list2, size2, &resultSize);
    
    printTuples(similar, resultSize);
    
    free(similar);
    similar = NULL;
    
    return 0;
}