#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    int size;
} Tuple;

typedef struct {
    int **pairs;
    int size;
} PairList;

PairList assign_pairs(Tuple *tuple) {
    PairList result;
    result.size = 0;
    result.pairs = NULL;
    
    if (tuple == NULL || tuple->elements == NULL || tuple->size <= 0) {
        return result;
    }
    
    int n = tuple->size;
    int max_pairs = n * (n - 1) / 2;
    
    result.pairs = (int **)malloc(max_pairs * sizeof(int *));
    if (result.pairs == NULL) {
        return result;
    }
    
    result.size = max_pairs;
    
    int pair_index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (tuple->elements[i] == tuple->elements[j]) {
                result.pairs[pair_index] = (int *)malloc(2 * sizeof(int));
                if (result.pairs[pair_index] == NULL) {
                    for (int k = 0; k < pair_index; k++) {
                        free(result.pairs[k]);
                    }
                    free(result.pairs);
                    result.pairs = NULL;
                    result.size = 0;
                    return result;
                }
                result.pairs[pair_index][0] = i;
                result.pairs[pair_index][1] = j;
                pair_index++;
            }
        }
    }
    
    result.size = pair_index;
    
    if (pair_index < max_pairs) {
        int **temp = (int **)realloc(result.pairs, pair_index * sizeof(int *));
        if (temp != NULL || pair_index == 0) {
            result.pairs = temp;
        }
    }
    
    return result;
}

void free_pair_list(PairList *pair_list) {
    if (pair_list == NULL || pair_list->pairs == NULL) {
        return;
    }
    
    for (int i = 0; i < pair_list->size; i++) {
        free(pair_list->pairs[i]);
    }
    free(pair_list->pairs);
    pair_list->pairs = NULL;
    pair_list->size = 0;
}

int main(void) {
    int elements[] = {1, 2, 3, 1, 4, 2, 1};
    int tuple_size = sizeof(elements) / sizeof(elements[0]);
    
    Tuple tuple;
    tuple.elements = elements;
    tuple.size = tuple_size;
    
    PairList pairs = assign_pairs(&tuple);
    
    printf("Tuple elements: ");
    for (int i = 0; i < tuple.size; i++) {
        printf("%d ", tuple.elements[i]);
    }
    printf("\n");
    
    printf("Found %d pairs with equal elements:\n", pairs.size);
    for (int i = 0; i < pairs.size; i++) {
        printf("Pair %d: indices (%d, %d) with values %d and %d\n", 
               i + 1, pairs.pairs[i][0], pairs.pairs[i][1],
               tuple.elements[pairs.pairs[i][0]], 
               tuple.elements[pairs.pairs[i][1]]);
    }
    
    free_pair_list(&pairs);
    
    int empty_elements[] = {};
    Tuple empty_tuple;
    empty_tuple.elements = empty_elements;
    empty_tuple.size = 0;
    
    PairList empty_pairs = assign_pairs(&empty_tuple);
    printf("Empty tuple found %d pairs\n", empty_pairs.size);
    free_pair_list(&empty_pairs);
    
    PairList null_pairs = assign_pairs(NULL);
    printf("NULL tuple found %d pairs\n", null_pairs.size);
    free_pair_list(&null_pairs);
    
    return 0;
}