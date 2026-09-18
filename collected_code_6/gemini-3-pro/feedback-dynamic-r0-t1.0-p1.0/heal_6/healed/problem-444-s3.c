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

TupleList* trimTuples(const TupleList *list, size_t k) {
    if (!list || !list->tuples) {
        return NULL;
    }

    TupleList *trimmedList = (TupleList *)malloc(sizeof(TupleList));
    if (!trimmedList) {
        return NULL;
    }

    size_t validCount = 0;
    for (size_t i = 0; i < list->count; ++i) {
        if (list->tuples[i].size != k) {
            validCount++;
        }
    }

    trimmedList->count = validCount;
    if (validCount == 0) {
        trimmedList->tuples = NULL;
        return trimmedList;
    }

    trimmedList->tuples = (Tuple *)calloc(trimmedList->count, sizeof(Tuple));
    if (!trimmedList->tuples) {
        free(trimmedList);
        return NULL;
    }

    size_t destIdx = 0;
    for (size_t i = 0; i < list->count; ++i) {
        if (list->tuples[i].size != k) {
            trimmedList->tuples[destIdx].size = list->tuples[i].size;
            if (list->tuples[i].size > 0) {
                trimmedList->tuples[destIdx].elements = (int *)malloc(list->tuples[i].size * sizeof(int));
                if (!trimmedList->tuples[destIdx].elements) {
                    for (size_t j = 0; j < destIdx; ++j) {
                        free(trimmedList->tuples[j].elements);
                    }
                    free(trimmedList->tuples);
                    free(trimmedList);
                    return NULL;
                }
                for (size_t j = 0; j < list->tuples[i].size; ++j) {
                    trimmedList->tuples[destIdx].elements[j] = list->tuples[i].elements[j];
                }
            } else {
                trimmedList->tuples[destIdx].elements = NULL;
            }
            destIdx++;
        }
    }

    return trimmedList;
}

void freeTupleList(TupleList *list) {
    if (list) {
        if (list->tuples) {
            for (size_t i = 0; i < list->count; ++i) {
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
    for (size_t i = 0; i < list->count; ++i) {
        printf("(");
        for (size_t j = 0; j < list->tuples[i].size; ++j) {
            printf("%d", list->tuples[i].elements[j]);
            if (j < list->tuples[i].size - 1) {
                printf(", ");
            }
        }
        if (list->tuples[i].size == 1) {
            printf(",)");
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
    char input[8192];
    if (fgets(input, sizeof(input), stdin) == NULL) return 0;

    TupleList list;
    list.tuples = malloc(1000 * sizeof(Tuple));
    list.count = 0;

    char *p = input;
    while (*p && *p != '[') p++;
    if (*p == '[') p++;

    while (*p && *p != ']') {
        if (*p == '(') {
            p++;
            Tuple t;
            t.elements = malloc(1000 * sizeof(int));
            t.size = 0;
            while (*p && *p != ')') {
                if (isdigit(*p) || *p == '-') {
                    t.elements[t.size++] = strtol(p, &p, 10);
                } else {
                    p++;
                }
            }
            if (*p == ')') p++;
            list.tuples[list.count++] = t;
        } else {
            p++;
        }
    }
    
    while (*p && *p != ']') p++;
    if (*p == ']') p++;

    size_t k = 0;
    while (*p) {
        if (isdigit(*p)) {
            k = strtoul(p, &p, 10);
            break;
        }
        p++;
    }

    TupleList *res = trimTuples(&list, k);
    printTupleList(res);

    freeTupleList(res);
    for (size_t i = 0; i < list.count; i++) {
        free(list.tuples[i].elements);
    }
    free(list.tuples);

    return 0;
}