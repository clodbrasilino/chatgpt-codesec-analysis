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

TupleList* trimTuples(const TupleList *list, size_t k) {
    if (!list) return NULL;

    TupleList *trimmedList = (TupleList *)malloc(sizeof(TupleList));
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

    trimmedList->tuples = (Tuple *)calloc(validCount, sizeof(Tuple));
    size_t destIdx = 0;
    for (size_t i = 0; i < list->count; ++i) {
        if (list->tuples[i].size != k) {
            trimmedList->tuples[destIdx].size = list->tuples[i].size;
            if (list->tuples[i].size > 0) {
                trimmedList->tuples[destIdx].elements = (int *)malloc(list->tuples[i].size * sizeof(int));
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
    char *input = malloc(1024 * 1024);
    if (!input) return 1;
    size_t len = fread(input, 1, 1024 * 1024 - 1, stdin);
    input[len] = '\0';

    TupleList list;
    list.tuples = malloc(100000 * sizeof(Tuple));
    list.count = 0;

    char *p = input;
    while (*p && *p != '[') p++;
    if (*p == '[') p++;

    while (*p && *p != ']') {
        if (*p == '(') {
            p++;
            Tuple t;
            int temp_elements[2048];
            t.size = 0;
            while (*p && *p != ')') {
                if (isdigit((unsigned char)*p) || (*p == '-' && isdigit((unsigned char)*(p + 1)))) {
                    temp_elements[t.size++] = strtol(p, &p, 10);
                } else {
                    p++;
                }
            }
            if (*p == ')') p++;
            t.elements = malloc(t.size * sizeof(int));
            if (t.size > 0) {
                memcpy(t.elements, temp_elements, t.size * sizeof(int));
            }
            list.tuples[list.count++] = t;
        } else {
            p++;
        }
    }

    if (*p == ']') p++;
    while (*p && !isdigit((unsigned char)*p) && *p != '-') p++;
    size_t k = 0;
    if (*p) {
        k = strtol(p, NULL, 10);
    }

    TupleList *res = trimTuples(&list, k);
    printTupleList(res);

    for (size_t i = 0; i < list.count; i++) {
        free(list.tuples[i].elements);
    }
    free(list.tuples);

    if (res) {
        for (size_t i = 0; i < res->count; i++) {
            free(res->tuples[i].elements);
        }
        free(res->tuples);
        free(res);
    }

    free(input);
    return 0;
}