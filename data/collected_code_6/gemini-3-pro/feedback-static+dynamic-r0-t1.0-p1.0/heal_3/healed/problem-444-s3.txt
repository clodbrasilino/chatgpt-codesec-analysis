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

TupleList* trimTuples(const TupleList *list) {
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
        if (list->tuples[i].size > 0) {
            Tuple *t = &trimmedList->tuples[trimmedList->count++];
            t->size = list->tuples[i].size;
            t->capacity = t->size;
            t->elements = (int *)malloc(t->size * sizeof(int));
            if (t->elements) {
                for (size_t j = 0; j < t->size; ++j) {
                    t->elements[j] = list->tuples[i].elements[j];
                }
            }
        }
    }
    return trimmedList;
}

void printTupleList(const TupleList *list) {
    if (!list || list->count == 0) {
        printf("[]\n");
        return;
    }
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
            if (list->tuples[i].size > 0) {
                free(list->tuples[i].elements);
            }
        }
        free(list->tuples);
        free(list);
    }
}

int main(void) {
    char *line1 = NULL;
    size_t len1 = 0;

    if (getline(&line1, &len1, stdin) == -1) {
        free(line1);
        return 0;
    }

    TupleList list;
    list.capacity = 16;
    list.tuples = (Tuple *)malloc(list.capacity * sizeof(Tuple));
    list.count = 0;

    char *p = line1;
    while (*p) {
        if (*p == '(') {
            p++;
            if (list.count >= list.capacity) {
                list.capacity *= 2;
                Tuple *temp = (Tuple *)realloc(list.tuples, list.capacity * sizeof(Tuple));
                if (!temp) break;
                list.tuples = temp;
            }
            
            Tuple *t = &list.tuples[list.count];
            t->capacity = 16;
            t->elements = (int *)malloc(t->capacity * sizeof(int));
            t->size = 0;
            
            while (*p && *p != ')') {
                if (isdigit((unsigned char)*p) || (*p == '-' && isdigit((unsigned char)*(p+1)))) {
                    if (t->size >= t->capacity) {
                        t->capacity *= 2;
                        int *temp_elements = (int *)realloc(t->elements, t->capacity * sizeof(int));
                        if (!temp_elements) break;
                        t->elements = temp_elements;
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

    TupleList *trimmed = trimTuples(&list);
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