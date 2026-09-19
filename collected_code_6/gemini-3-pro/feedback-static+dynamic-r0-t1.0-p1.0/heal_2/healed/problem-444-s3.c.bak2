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
    
    trimmedList->tuples = (Tuple *)malloc((list->count > 0 ? list->count : 1) * sizeof(Tuple));
    trimmedList->count = 0;
    
    for (size_t i = 0; i < list->count; ++i) {
        if (list->tuples[i].size != k) {
            Tuple *t = &trimmedList->tuples[trimmedList->count++];
            t->size = list->tuples[i].size;
            if (t->size > 0) {
                t->elements = (int *)malloc(t->size * sizeof(int));
                for (size_t j = 0; j < t->size; ++j) {
                    t->elements[j] = list->tuples[i].elements[j];
                }
            } else {
                t->elements = NULL;
            }
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
            } else if (list->tuples[i].size == 1) {
                printf(",");
            }
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
    char *line1 = NULL;
    size_t cap1 = 0;
    if (getline(&line1, &cap1, stdin) <= 0) {
        free(line1);
        return 0;
    }
    
    char *line2 = NULL;
    size_t cap2 = 0;
    if (getline(&line2, &cap2, stdin) <= 0) {
        free(line1);
        free(line2);
        return 0;
    }

    TupleList list;
    size_t max_tuples = 16;
    list.tuples = (Tuple *)malloc(max_tuples * sizeof(Tuple));
    list.count = 0;

    char *p = line1;
    while (*p) {
        if (*p == '(') {
            p++;
            if (list.count >= max_tuples) {
                max_tuples *= 2;
                list.tuples = (Tuple *)realloc(list.tuples, max_tuples * sizeof(Tuple));
            }
            Tuple *t = &list.tuples[list.count];
            size_t max_elems = 16;
            t->elements = (int *)malloc(max_elems * sizeof(int));
            t->size = 0;
            while (*p && *p != ')') {
                if (isdigit((unsigned char)*p) || (*p == '-' && isdigit((unsigned char)*(p+1)))) {
                    if (t->size >= max_elems) {
                        max_elems *= 2;
                        t->elements = (int *)realloc(t->elements, max_elems * sizeof(int));
                    }
                    t->elements[t->size++] = strtol(p, &p, 10);
                } else {
                    p++;
                }
            }
            list.count++;
        }
        if (*p) p++;
    }

    size_t k = strtoul(line2, NULL, 10);

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
    free(line2);

    return 0;
}