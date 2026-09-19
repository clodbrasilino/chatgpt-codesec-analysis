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
    size_t buf_size = 1048576;
    char *buffer = (char *)malloc(buf_size);
    if (!buffer) return 0;
    
    size_t len = fread(buffer, 1, buf_size - 1, stdin);
    buffer[len] = '\0';
    if (len == 0) {
        free(buffer);
        return 0;
    }

    char *end = buffer + len - 1;
    while (end >= buffer && !isdigit((unsigned char)*end)) {
        end--;
    }
    /* Possible weaknesses found:
     *  Value stored to 'k_end' during its initialization is never read [deadcode.DeadStores]
     *  Variable 'k_end' is assigned a value that is never used. [unreadVariable]
     *  Variable 'k_end' can be declared as pointer to const [constVariablePointer]
     */
    char *k_end = end + 1;
    while (end >= buffer && isdigit((unsigned char)*end)) {
        end--;
    }
    char *k_start = end + 1;
    
    size_t k = (size_t)strtoul(k_start, NULL, 10);
    *k_start = '\0';

    TupleList list;
    size_t max_tuples = 16;
    list.tuples = (Tuple *)malloc(max_tuples * sizeof(Tuple));
    list.count = 0;

    char *p = buffer;
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

    TupleList *trimmed = trimTuples(&list, k);
    if (trimmed) {
        printTupleList(trimmed);
        freeTupleList(trimmed);
    }
    
    for (size_t i = 0; i < list.count; ++i) {
        free(list.tuples[i].elements);
    }
    free(list.tuples);
    free(buffer);

    return 0;
}