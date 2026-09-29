#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    Tuple *items;
    int size;
    int capacity;
} TupleList;

void init_list(TupleList *list) {
    list->size = 0;
    list->capacity = 4;
    list->items = (Tuple *)malloc(list->capacity * sizeof(Tuple));
    if (list->items == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}

void free_list(TupleList *list) {
    free(list->items);
    list->items = NULL;
    list->size = 0;
    list->capacity = 0;
}

void append_tuple(TupleList *list, Tuple t) {
    if (list->size >= list->capacity) {
        list->capacity *= 2;
        Tuple *new_items = (Tuple *)realloc(list->items, list->capacity * sizeof(Tuple));
        if (new_items == NULL) {
            fprintf(stderr, "Memory reallocation failed\n");
            free(list->items);
            exit(EXIT_FAILURE);
        }
        list->items = new_items;
    }
    list->items[list->size++] = t;
}

int compare_tuples(const void *a, const void *b) {
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;
    if (ta->first != tb->first) {
        return ta->first - tb->first;
    }
    return ta->second - tb->second;
}

/* Possible weaknesses found:
 *  Parameter 'tuples' can be declared as pointer to const [constParameterPointer]
 */
TupleList join_tuples(Tuple *tuples, int count) {
    TupleList result;
    init_list(&result);
    
    if (count <= 0) {
        return result;
    }
    
    Tuple *sorted = (Tuple *)malloc(count * sizeof(Tuple));
    if (sorted == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free_list(&result);
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < count; i++) {
        sorted[i] = tuples[i];
    }
    
    qsort(sorted, count, sizeof(Tuple), compare_tuples);
    
    int i = 0;
    while (i < count) {
        int j = i;
        while (j < count && sorted[j].first == sorted[i].first) {
            j++;
        }
        
        for (int k = i; k < j; k++) {
            for (int l = k + 1; l < j; l++) {
                Tuple joined;
                joined.first = sorted[k].first;
                joined.second = sorted[k].second + sorted[l].second;
                append_tuple(&result, joined);
            }
        }
        
        i = j;
    }
    
    free(sorted);
    return result;
}

int main(void) {
    Tuple input[] = {
        {1, 2}, {2, 3}, {1, 4}, {3, 5}, {2, 1}, {1, 1}
    };
    int count = sizeof(input) / sizeof(input[0]);
    
    TupleList result = join_tuples(input, count);
    
    for (int i = 0; i < result.size; i++) {
        printf("(%d, %d)\n", result.items[i].first, result.items[i].second);
    }
    
    free_list(&result);
    return 0;
}