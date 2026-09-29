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

    size_t alloc_count = inputList->count > 0 ? inputList->count : 1;
    resultList->tuples = malloc(alloc_count * sizeof(Tuple));
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
            
            if (result->size > 0) {
                result->elements = malloc(result->size * sizeof(int));
                if (!result->elements) {
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
            } else {
                result->elements = NULL;
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
                if (list->tuples[i].elements) {
                    free(list->tuples[i].elements);
                }
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
    int c;
    size_t capacity = 8192;
    size_t len = 0;
    char *input = malloc(capacity);
    if (!input) return 0;
    
    while ((c = getchar()) != EOF) {
        if (len + 1 >= capacity) {
            capacity *= 2;
            char *temp = realloc(input, capacity);
            if (!temp) {
                free(input);
                return 0;
            }
            input = temp;
        }
        input[len++] = (char)c;
    }
    input[len] = '\0';
    
    TupleList inputList = {NULL, 0};
    inputList.tuples = malloc(10000 * sizeof(Tuple));
    if (!inputList.tuples) {
        free(input);
        return 0;
    }
    
    char *p = input;
    char *end_bracket = strrchr(input, ']');
    
    while (*p && (!end_bracket || p < end_bracket)) {
        if (*p == '(') {
            p++;
            Tuple t;
            t.size = 0;
            t.elements = malloc(1000 * sizeof(int));
            if (!t.elements) break;
            
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
    
    size_t k = 0;