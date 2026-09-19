#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int *elements;
    size_t size;
    size_t capacity;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
    size_t capacity;
} TupleList;
 /* Possible weaknesses found:
  *  test case 2 failed: expected '[(8, 4), (8, 12), (1, 7), (6, 9)]', got <no output>
  *  test case 1 failed: expected '[(3, 2, 1), (4, 9, 2), (1, 2, 3), (8, 2, 1)]', got <no output>
  *  test case 0 failed: expected '[(2,), (9,), (2,), (2,)]', got <no output>
  */

TupleList* trimTuples(const TupleList *list, size_t k) {
    if (!list) return NULL;
    TupleList *trimmedList = (TupleList *)malloc(sizeof(TupleList));
    if (!trimmedList) return NULL;
    
    trimmedList->tuples = (Tuple *)malloc(list->count * sizeof(Tuple));
    if (!trimmedList->tuples) {
        free(trimmedList);
        return NULL;
    }
    trimmedList->count = 0;
    trimmedList->capacity = list->count;
    
    for (size_t i = 0; i < list->count; ++i) {
        if (list->tuples[i].size != k) {
            Tuple *t = &trimmedList->tuples[trimmedList->count++];
            t->size = list->tuples[i].size;
            t->capacity = t->size;
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
    size_t buffer_size = 2000000;
    char *buf = (char *)malloc(buffer_size);
    if (!buf) return 1;
    
    size_t len = fread(buf, 1, buffer_size - 1, stdin);
    buf[len] = '\0';
    
    if (len == 0) {
        free(buf);
        return 0;
    }
    
    long end_idx = len - 1;
    while (end_idx >= 0 && !isdigit((unsigned char)buf[end_idx])) end_idx--;
    while (end_idx >= 0 && isdigit((unsigned char)buf[end_idx])) end_idx--;
    
    char *k_ptr = buf + end_idx + 1;
    size_t k = strtoul(k_ptr, NULL, 10);
    *k_ptr = '\0';

    TupleList list;
    list.capacity = 1000;
    list.tuples = (Tuple *)malloc(list.capacity * sizeof(Tuple));
    list.count = 0;

    char *p = buf;
    
    while (*p) {
        if (*p == '(') {
            p++;
            if (list.count == list.capacity) {
                list.capacity *= 2;
                list.tuples = (Tuple *)realloc(list.tuples, list.capacity * sizeof(Tuple));
            }
            Tuple *t = &list.tuples[list.count];
            t->capacity = 10;
            t->elements = (int *)malloc(t->capacity * sizeof(int));
            t->size = 0;
            
            while (*p && *p != ')') {
                if (isdigit((unsigned char)*p) || (*p == '-' && isdigit((unsigned char)p[1]))) {
                    if (t->size == t->capacity) {
                        t->capacity *= 2;
                        t->elements = (int *)realloc(t->elements, t->capacity * sizeof(int));
                    }
                    t->elements[t->size++] = strtol(p, &p, 10);
                } else {
                    p++;
                }
            }
            if (*p == ')') {
                p++;
            }
            list.count++;
        } else {
            p++;
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
    free(buf);
    
    return 0;
}