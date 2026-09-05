#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    void *data;
    size_t element_size;
    size_t size;
} Tuple;

typedef struct {
    void *data;
    size_t element_size;
    size_t size;
} List;

typedef int (*CompareFunc)(const void *, const void *);

int count_occurrences(const Tuple *tuple, const List *list, CompareFunc compare, size_t *counts) {
    if (tuple == NULL || list == NULL || compare == NULL || counts == NULL) {
        return -1;
    }
    
    if (tuple->data == NULL || list->data == NULL) {
        return -1;
    }
    
    if (tuple->element_size != list->element_size) {
        return -1;
    }
    
    for (size_t i = 0; i < list->size; i++) {
        counts[i] = 0;
    }
    
    for (size_t i = 0; i < list->size; i++) {
        const void *list_elem = (const char *)list->data + (i * list->element_size);
        
        for (size_t j = 0; j < tuple->size; j++) {
            const void *tuple_elem = (const char *)tuple->data + (j * tuple->element_size);
            
            if (compare(list_elem, tuple_elem) == 0) {
                counts[i]++;
            }
        }
    }
    
    return 0;
}

int compare_int(const void *a, const void *b) {
    if (a == NULL || b == NULL) {
        return -1;
    }
    
    int int_a = *(const int *)a;
    int int_b = *(const int *)b;
    
    if (int_a < int_b) {
        return -1;
    } else if (int_a > int_b) {
        return 1;
    }
    return 0;
}

int main(void) {
    int tuple_data[] = {1, 2, 3, 2, 4, 2, 5, 1, 2};
    int list_data[] = {1, 2, 3, 6};
    
    Tuple tuple = {
        .data = tuple_data,
        .element_size = sizeof(int),
        .size = sizeof(tuple_data) / sizeof(tuple_data[0])
    };
    
    List list = {
        .data = list_data,
        .element_size = sizeof(int),
        .size = sizeof(list_data) / sizeof(list_data[0])
    };
    
    size_t *counts = (size_t *)calloc(list.size, sizeof(size_t));
    if (counts == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    if (count_occurrences(&tuple, &list, compare_int, counts) != 0) {
        fprintf(stderr, "Error counting occurrences\n");
        free(counts);
        counts = NULL;
        return EXIT_FAILURE;
    }
    
    printf("Occurrences:\n");
    for (size_t i = 0; i < list.size; i++) {
        printf("Element %d: %zu times\n", list_data[i], counts[i]);
    }
    
    free(counts);
    counts = NULL;
    
    return EXIT_SUCCESS;
}