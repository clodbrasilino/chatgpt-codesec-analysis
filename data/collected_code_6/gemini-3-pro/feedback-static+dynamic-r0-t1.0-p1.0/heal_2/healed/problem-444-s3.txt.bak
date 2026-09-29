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
    if (!list) return NULL;
    TupleList *trimmedList = (TupleList *)malloc(sizeof(TupleList));
    if (!trimmedList) return NULL;
    
    trimmedList->tuples = (Tuple *)malloc(list->count * sizeof(Tuple));
    trimmedList->count = 0;
    
    for (size_t i = 0; i < list->count; ++i) {
        if (list->tuples[i].size != k) {
            Tuple *t = &trimmedList->tuples[trimmedList->count++];
            t->size = list->tuples[i].size;
            t->elements = (int *)malloc(t->size * sizeof(int));
            for (size_t j = 0; j < t->size; ++j) {
                t->elements[j] = list->tuples[i].elements[j];
            }
        }
    }
    return trimmedList;
}

void printTupleList(const TupleList *list) {
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
            printf(",");
        }
        printf(")");
        if (i < list->count - 1) printf(", ");
    }
    printf("]\n");
}

void freeTupleList(TupleList *list) {
    if (list) {
        for (size_t i = 0; i < list->count; ++i) {
            free(list->tuples[i].elements);
        }
        free(list->tuples);
        free(list);
    }
}

int main(void) {
    size_t buffer_size = 200000;
    char *line1 = (char *)malloc(buffer_size);
    if (!line1) return 1;
    
    if (!fgets(line1, buffer_size, stdin)) {
        free(line1);
        return 0;
    }

    TupleList list;
    list.tuples = (Tuple *)malloc(10000 * sizeof(Tuple));
    list.count = 0;

    char *p = line1;
    while (*p) {
        if (*p == '(') {
            p++;
            Tuple *t = &list.tuples[list.count];
            t->elements = (int *)malloc(1000 * sizeof(int));
            t->size = 0;
            while (*p && *p != ')') {
                if (isdigit((unsigned char)*p) || (*p == '-' && isdigit((unsigned char)p[1]))) {
                    t->elements[t->size++] = strtol(p, &p, 10);
                } else {
                    p++;
                }
            }
            list.count++;
        }
        if (*p) p++;
    }

    size_t k = 0;
    if (scanf("%zu", &k) != 1) {
        char line2[256];
        if (fgets(line2, sizeof(line2), stdin)) {
            k = strtoul(line2, NULL, 10);
        }
    }

    TupleList *trimmed = trimTuples(&list, k);
    if (trimmed) {
        printTupleList(trimmed);
        freeTupleList(trimmed);
    }
    
    for (size_t i = 0; i < list.count; ++i) {
        free(list.tuples[i].elements);
    }
    free(list.tuples);
    free(line1);

    return 0;
}