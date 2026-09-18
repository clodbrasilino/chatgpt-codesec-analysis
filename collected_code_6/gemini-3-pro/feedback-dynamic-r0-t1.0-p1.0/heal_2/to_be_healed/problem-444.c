#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
} TupleList;
 /* Possible weaknesses found:
  *  test case 2 failed: expected '[(8, 4), (8, 12), (1, 7), (6, 9)]', got <no output>
  *  test case 0 failed: expected '[(2,), (9,), (2,), (2,)]', got <no output>
  *  test case 1 failed: expected '[(3, 2, 1), (4, 9, 2), (1, 2, 3), (8, 2, 1)]', got <no output>
  */

TupleList* trimTuples(const TupleList *inputList, size_t k) {
    if (!inputList || !inputList->tuples) {
        return NULL;
    }

    TupleList *resultList = malloc(sizeof(TupleList));
    if (!resultList) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < inputList->count; i++) {
        if (inputList->tuples[i].size != k) {
            count++;
        }
    }

    resultList->count = count;
    resultList->tuples = malloc(count * sizeof(Tuple));
    if (!resultList->tuples && count > 0) {
        free(resultList);
        return NULL;
    }

    size_t idx = 0;
    for (size_t i = 0; i < inputList->count; i++) {
        if (inputList->tuples[i].size != k) {
            Tuple *current = &inputList->tuples[i];
            Tuple *result = &resultList->tuples[idx++];
            
            result->size = current->size;
            if (result->size > 0) {
                result->elements = malloc(result->size * sizeof(int));
                if (!result->elements) {
                    for (size_t j = 0; j < idx - 1; j++) {
                        free(resultList->tuples[j].elements);
                    }
                    free(resultList->tuples);
                    free(resultList);
                    return NULL;
                }
                for (size_t j = 0; j < result->size; j++) {
                    result->elements[j] = current->elements[j];
                }
            } else {
                result->elements = NULL;
            }
        }
    }

    return resultList;
}

void freeTupleList(TupleList *list) {
    if (list) {
        if (list->tuples) {
            for (size_t i = 0; i < list->count; i++) {
                free(list->tuples[i].elements);
            }
            free(list->tuples);
        }
        free(list);
    }
}

void printTupleList(const TupleList *list) {
    if (!list) return;
    printf("[");
    for (size_t i = 0; i < list->count; i++) {
        printf("(");
        for (size_t j = 0; j < list->tuples[i].size; j++) {
            printf("%d", list->tuples[i].elements[j]);
            if (j < list->tuples[i].size - 1 || list->tuples[i].size == 1) {
                printf(", ");
            }
        }
        if (list->tuples[i].size == 1) {
            printf(")");
        } else {
            printf(")");
        }
        if (i < list->count - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void) {
    char line[1024];
    if (!fgets(line, sizeof(line), stdin)) return 0;
    char k_line[256];
    if (!fgets(k_line, sizeof(k_line), stdin)) return 0;
    
    size_t k = strtoul(k_line, NULL, 10);
    
    TupleList inputList;
    inputList.count = 0;
    inputList.tuples = malloc(100 * sizeof(Tuple));
    
    char *ptr = line;
    while ((ptr = strchr(ptr, '(')) != NULL) {
        ptr++;
        inputList.tuples[inputList.count].size = 0;
        inputList.tuples[inputList.count].elements = malloc(100 * sizeof(int));
        
        while (*ptr && *ptr != ')') {
            if (isdigit((unsigned char)*ptr) || *ptr == '-') {
                inputList.tuples[inputList.count].elements[inputList.tuples[inputList.count].size++] = strtol(ptr, &ptr, 10);
            } else {
                ptr++;
            }
        }
        inputList.count++;
    }
    
    TupleList *trimmed = trimTuples(&inputList, k);
    printTupleList(trimmed);
    
    freeTupleList(trimmed);
    for (size_t i = 0; i < inputList.count; i++) free(inputList.tuples[i].elements);
    free(inputList.tuples);
    
    return 0;
}