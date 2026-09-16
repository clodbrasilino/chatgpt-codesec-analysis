#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    int size;
} Tuple;

typedef struct {
    int **tuples;
    int *sizes;
    int count;
} TupleList;

typedef struct {
    TupleList combination;
    int sum;
} Combination;

void initCombination(Combination *comb) {
    comb->combination.tuples = NULL;
    comb->combination.sizes = NULL;
    comb->combination.count = 0;
    comb->sum = 0;
}

void freeCombination(Combination *comb) {
    if (comb->combination.tuples != NULL) {
        for (int i = 0; i < comb->combination.count; i++) {
            free(comb->combination.tuples[i]);
        }
        free(comb->combination.tuples);
    }
    free(comb->combination.sizes);
    comb->combination.tuples = NULL;
    comb->combination.sizes = NULL;
    comb->combination.count = 0;
    comb->sum = 0;
}

void copyCombination(Combination *dest, const Combination *src) {
    dest->combination.count = src->combination.count;
    dest->sum = src->sum;
    
    if (src->combination.count == 0) {
        dest->combination.tuples = NULL;
        dest->combination.sizes = NULL;
        return;
    }
    
    dest->combination.tuples = (int **)malloc(src->combination.count * sizeof(int *));
    dest->combination.sizes = (int *)malloc(src->combination.count * sizeof(int));
    
    if (dest->combination.tuples == NULL || dest->combination.sizes == NULL) {
        free(dest->combination.tuples);
        free(dest->combination.sizes);
        dest->combination.tuples = NULL;
        dest->combination.sizes = NULL;
        dest->combination.count = 0;
        dest->sum = 0;
        return;
    }
    
    for (int i = 0; i < src->combination.count; i++) {
        dest->combination.sizes[i] = src->combination.sizes[i];
        dest->combination.tuples[i] = (int *)malloc(dest->combination.sizes[i] * sizeof(int));
        
        if (dest->combination.tuples[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dest->combination.tuples[j]);
            }
            free(dest->combination.tuples);
            free(dest->combination.sizes);
            dest->combination.tuples = NULL;
            dest->combination.sizes = NULL;
            dest->combination.count = 0;
            dest->sum = 0;
            return;
        }
        
        for (int j = 0; j < dest->combination.sizes[i]; j++) {
            dest->combination.tuples[i][j] = src->combination.tuples[i][j];
        }
    }
}

int calculateTupleSum(const Tuple *tuple) {
    int sum = 0;
    for (int i = 0; i < tuple->size; i++) {
        sum += tuple->elements[i];
    }
    return sum;
}

void findCombinationsRecursive(TupleList *tupleList, int targetSum, int startIndex, 
                               Combination *currentCombination, Combination **results, 
                               int *resultCount, int *resultCapacity) {
    if (currentCombination->sum == targetSum) {
        if (*resultCount >= *resultCapacity) {
            *resultCapacity *= 2;
            Combination *newResults = (Combination *)realloc(*results, *resultCapacity * sizeof(Combination));
            if (newResults == NULL) {
                return;
            }
            *results = newResults;
        }
        
        initCombination(&(*results)[*resultCount]);
        copyCombination(&(*results)[*resultCount], currentCombination);
        (*resultCount)++;
        return;
    }
    
    if (currentCombination->sum > targetSum) {
        return;
    }
    
    for (int i = startIndex; i < tupleList->count; i++) {
        int tupleSum = calculateTupleSum(&(Tuple){tupleList->tuples[i], tupleList->sizes[i]});
        
        if (currentCombination->sum + tupleSum <= targetSum) {
            Combination newCombination;
            initCombination(&newCombination);
            copyCombination(&newCombination, currentCombination);
            
            newCombination.sum += tupleSum;
            newCombination.combination.count++;
            
            int **newTuples = (int **)realloc(newCombination.combination.tuples, 
                                               newCombination.combination.count * sizeof(int *));
            int *newSizes = (int *)realloc(newCombination.combination.sizes, 
                                            newCombination.combination.count * sizeof(int));
            
            if (newTuples == NULL || newSizes == NULL) {
                freeCombination(&newCombination);
                continue;
            }
            
            newCombination.combination.tuples = newTuples;
            newCombination.combination.sizes = newSizes;
            
            newCombination.combination.tuples[newCombination.combination.count - 1] = 
                (int *)malloc(tupleList->sizes[i] * sizeof(int));
            
            if (newCombination.combination.tuples[newCombination.combination.count - 1] == NULL) {
                freeCombination(&newCombination);
                continue;
            }
            
            for (int j = 0; j < tupleList->sizes[i]; j++) {
                newCombination.combination.tuples[newCombination.combination.count - 1][j] = 
                    tupleList->tuples[i][j];
            }
            newCombination.combination.sizes[newCombination.combination.count - 1] = tupleList->sizes[i];
            
            findCombinationsRecursive(tupleList, targetSum, i + 1, &newCombination, 
                                      results, resultCount, resultCapacity);
            
            freeCombination(&newCombination);
        }
    }
}

Combination *findCombinations(TupleList *tupleList, int targetSum, int *resultCount) {
    if (tupleList == NULL || tupleList->count <= 0 || targetSum <= 0) {
        *resultCount = 0;
        return NULL;
    }
    
    int capacity = 10;
    Combination *results = (Combination *)malloc(capacity * sizeof(Combination));
    if (results == NULL) {
        *resultCount = 0;
        return NULL;
    }
    
    Combination currentCombination;
    initCombination(&currentCombination);
    
    *resultCount = 0;
    
    findCombinationsRecursive(tupleList, targetSum, 0, &currentCombination, 
                              &results, resultCount, &capacity);
    
    freeCombination(&currentCombination);
    
    if (*resultCount == 0) {
        free(results);
        return NULL;
    }
    
    return results;
}

void freeResults(Combination *results, int resultCount) {
    if (results == NULL) {
        return;
    }
    
    for (int i = 0; i < resultCount; i++) {
        freeCombination(&results[i]);
    }
    free(results);
}

void printCombination(const Combination *comb) {
    printf("Sum: %d, Tuples: [", comb->sum);
    for (int i = 0; i < comb->combination.count; i++) {
        printf("(");
        for (int j = 0; j < comb->combination.sizes[i]; j++) {
            printf("%d", comb->combination.tuples[i][j]);
            if (j < comb->combination.sizes[i] - 1) {
                printf(",");
            }
        }
        printf(")");
        if (i < comb->combination.count - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void) {
    int tuple1[] = {1, 2};
    int tuple2[] = {3, 4};
    int tuple3[] = {5, 6};
    int tuple4[] = {2, 3};
    
    int *tuples[] = {tuple1, tuple2, tuple3, tuple4};
    int sizes[] = {2, 2, 2, 2};
    
    TupleList tupleList;
    tupleList.tuples = tuples;
    tupleList.sizes = sizes;
    tupleList.count = 4;
    
    int targetSum = 10;
    int resultCount = 0;
    
    Combination *results = findCombinations(&tupleList, targetSum, &resultCount);
    
    printf("Target sum: %d\n", targetSum);
    printf("Number of combinations found: %d\n", resultCount);
    
    for (int i = 0; i < resultCount; i++) {
        printf("Combination %d: ", i + 1);
        printCombination(&results[i]);
    }
    
    freeResults(results, resultCount);
    
    return 0;
}