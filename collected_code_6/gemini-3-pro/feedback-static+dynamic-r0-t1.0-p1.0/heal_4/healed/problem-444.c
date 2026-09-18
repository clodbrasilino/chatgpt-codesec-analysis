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

TupleList* trimTuples(const TupleList *inputList, size_t k) {
    if (!inputList || !inputList->tuples) {
        return NULL;
    }

    TupleList *resultList = malloc(sizeof(TupleList));
    if (!resultList) {
        return NULL;
    }

    resultList->tuples = malloc(inputList->count * sizeof(Tuple));
    if (!resultList->tuples) {
        free(resultList);
        return NULL;
    }

    resultList->count = 0;

    for (size_t i = 0; i < inputList->count; i++) {
        Tuple *current = &inputList->tuples[i];

        if (current->size != k) {
            Tuple *result = &resultList->tuples[resultList->count];
            result->size = current->size;
            result->elements = malloc(result->size * sizeof(int));
            
            if (!result->elements && result->size > 0) {
                for (size_t j = 0; j < resultList->count; j++) {
                    free(resultList->tuples[j].elements);
                }
                free(resultList->tuples);
                free(resultList);
                return NULL;
            }
            
            for (size_t j = 0; j < result->size; j++) {
                result->elements[j] = current->elements[j];
            }
            resultList->count++;
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
            if (j < list->tuples[i].size - 1) {
                printf(", ");
            }
        }
        if (list->tuples[i].size == 1) {
            printf(",");
        }
        printf(")");
        if (i < list->count - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void) {
    char line[1024];
    if (!fgets(line, sizeof(line), stdin)) return 0;
    
    char k_line[64];
    if (!fgets(k_line, sizeof(k_line), stdin)) return 0;
    size_t k = strtoull(k_line, NULL, 10);
    
    TupleList inputList = {NULL, 0};
    inputList.tuples = malloc(100 * sizeof(Tuple));
    
    char *p = line;
    while (*p && *p != ']') {
        if (*p == '(') {
            p++;
            Tuple t = {malloc(100 * sizeof(int)), 0};
            while (*p && *p != ')') {
                if (isdigit((unsigned char)*p) || *p == '-') {
                    t.elements[t.size++] = strtol(p, &p, 10);
                } else {
                    p++;
                }
            }
            inputList.tuples[inputList.count++] = t;
        }
        p++;
    }
    
    TupleList *resultList = trimTuples(&inputList, k);
    if (resultList) {
        printTupleList(resultList);
        freeTupleList(resultList);
    }
    
    for (size_t i = 0; i < inputList.count; i++) {
        free(inputList.tuples[i].elements);
    }
    free(inputList.tuples);
    
    return 0;
}