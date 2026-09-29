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
    if (!inputList || !inputList->tuples) return NULL;
    TupleList *resultList = malloc(sizeof(TupleList));
    resultList->tuples = malloc(inputList->count * sizeof(Tuple));
    resultList->count = 0;
    for (size_t i = 0; i < inputList->count; i++) {
        Tuple *current = &inputList->tuples[i];
        if (current->size != k) {
            Tuple *result = &resultList->tuples[resultList->count];
            result->size = current->size;
            if (result->size > 0) {
                result->elements = malloc(result->size * sizeof(int));
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
    size_t line_size = 1048576;
    char *line = malloc(line_size);
    if (!line) return 1;
    size_t len = fread(line, 1, line_size - 1, stdin);
    line[len] = '\0';

    size_t k = 0;
    char *bracket_end = strrchr(line, ']');
    if (bracket_end) {
        char *k_pos = bracket_end + 1;
        while (*k_pos && !isdigit((unsigned char)*k_pos)) k_pos++;
        if (*k_pos) {
            k = strtoull(k_pos, NULL, 10);
        }
    }

    TupleList inputList = {NULL, 0};
    size_t listCapacity = 128;
    inputList.tuples = malloc(listCapacity * sizeof(Tuple));
    
    char *p = line;
    if (!bracket_end) bracket_end = line + len;
    
    while (*p && p < bracket_end) {
        if (*p == '(') {
            p++;
            size_t tupleCapacity = 16;
            Tuple t;
            t.size = 0;
            t.elements = malloc(tupleCapacity * sizeof(int));
            
            while (*p && *p != ')') {
                if (isdigit((unsigned char)*p) || (*p == '-' && isdigit((unsigned char)*(p+1)))) {
                    if (t.size >= tupleCapacity) {
                        tupleCapacity *= 2;
                        t.elements = realloc(t.elements, tupleCapacity * sizeof(int));
                    }
                    char *next_p;
                    t.elements[t.size++] = strtol(p, &next_p, 10);
                    p = next_p;
                } else {
                    p++;
                }
            }
            if (inputList.count >= listCapacity) {
                listCapacity *= 2;
                inputList.tuples = realloc(inputList.tuples, listCapacity * sizeof(Tuple));
            }
            inputList.tuples[inputList.count++] = t;
        } else {
            p++;
        }
    }
    
    TupleList *resultList = trimTuples(&inputList, k);
    printTupleList(resultList);
    
    freeTupleList(resultList);
    for (size_t i = 0; i < inputList.count; i++) {
        free(inputList.tuples[i].elements);
    }
    free(inputList.tuples);
    free(line);
    
    return 0;
}