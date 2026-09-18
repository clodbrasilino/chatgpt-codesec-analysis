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
    
    trimmedList->count = 0;
    trimmedList->capacity = list->count;
    trimmedList->tuples = (Tuple *)malloc(trimmedList->capacity * sizeof(Tuple));
    
    if (!trimmedList->tuples && trimmedList->capacity > 0) {
        free(trimmedList);
        return NULL;
    }

    for (size_t i = 0; i < list->count; i++) {
        if (list->tuples[i].size == k) {
            continue;
        }
        
        size_t newSize = list->tuples[i].size;
        Tuple *dest = &trimmedList->tuples[trimmedList->count];
        dest->size = newSize;
        dest->capacity = newSize;
        
        if (newSize > 0) {
            dest->elements = (int *)malloc(newSize * sizeof(int));
            if (dest->elements && list->tuples[i].elements) {
                memcpy(dest->elements, list->tuples[i].elements, newSize * sizeof(int));
            }
        } else {
            dest->elements = NULL;
        }
        trimmedList->count++;
    }
    
    return trimmedList;
}

void freeTupleList(TupleList *list) {
    if (!list) return;
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
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:98,execs:17,op:havoc,rep:1; likely memory-safety defect
  */

int main(void) {
    char input[4096];
    if (!fgets(input, sizeof(input), stdin)) return 0;
    
    char *k_str_pos = strrchr(input, ']');
    if (!k_str_pos) return 0;
    
    int k = 0;
    sscanf(k_str_pos + 1, "%d", &k);
    
    TupleList list;
    list.capacity = 100;
    list.count = 0;
    list.tuples = (Tuple *)malloc(list.capacity * sizeof(Tuple));
    
    char *p = input;
    while (*p && p < k_str_pos) {
        if (*p == '(') {
            p++;
            Tuple t;
            t.capacity = 20;
            t.size = 0;
            t.elements = (int*)malloc(t.capacity * sizeof(int));
            while (*p && *p != ')') {
                if (isdigit(*p) || *p == '-') {
                    t.elements[t.size++] = strtol(p, &p, 10);
                } else {
                    p++;
                }
            }
            list.tuples[list.count++] = t;
        } else {
            p++;
        }
    }
    
    TupleList *trimmed = trimTuples(&list, k);
    if (trimmed) {
        printf("[");
        for (size_t i = 0; i < trimmed->count; i++) {
            printf("(");
            for (size_t j = 0; j < trimmed->tuples[i].size; j++) {
                printf("%d", trimmed->tuples[i].elements[j]);
                if (trimmed->tuples[i].size == 1) {
                    printf(",");
                } else if (j < trimmed->tuples[i].size - 1) {
                    printf(", ");
                }
            }
            printf(")");
            if (i < trimmed->count - 1) {
                printf(", ");
            }
        }
        printf("]\n");
        freeTupleList(trimmed);
    }
    
    freeTupleList(&list);
    return 0;
}