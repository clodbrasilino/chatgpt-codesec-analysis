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
    char buffer[16384];
    size_t len = fread(buffer, 1, sizeof(buffer) - 1, stdin);
    if (len == 0) return 0;
    buffer[len] = '\0';
    
    char *end_bracket = strrchr(buffer, ']');
    size_t k = 0;
    if (end_bracket != NULL) {
        char *k_str = end_bracket + 1;
        while (*k_str) {
            if (isdigit((unsigned char)*k_str)) {
                k = strtoul(k_str, NULL, 10);
                break;
            }
            k_str++;
        }
    }
    
    TupleList inputList;
    inputList.count = 0;
    inputList.tuples = malloc(1000 * sizeof(Tuple));
    
    char *ptr = buffer;
    while ((ptr = strchr(ptr, '(')) != NULL && ptr < end_bracket) {
        ptr++;
        inputList.tuples[inputList.count].size = 0;
        inputList.tuples[inputList.count].elements = malloc(1000 * sizeof(int));
        
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