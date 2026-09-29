#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int *data;
    size_t size;
} List;

typedef struct {
    int *data;
    size_t size;
} Tuple;

typedef struct {
    int element;
    size_t count;
    int found;
} ElementCount;

void count_occurrences(const List *list, const Tuple *tuple, ElementCount **result, size_t *result_size) {
    if (list == NULL || tuple == NULL || result == NULL || result_size == NULL) {
        if (result_size != NULL) {
            *result_size = 0;
        }
        if (result != NULL) {
            *result = NULL;
        }
        return;
    }
    
    *result = NULL;
    *result_size = 0;
    
    if (list->size == 0 || tuple->size == 0) {
        return;
    }
    
    if (list->size > SIZE_MAX / sizeof(ElementCount)) {
        return;
    }
    
    ElementCount *counts = (ElementCount *)malloc(list->size * sizeof(ElementCount));
    if (counts == NULL) {
        return;
    }
    
    for (size_t i = 0; i < list->size; i++) {
        counts[i].element = list->data[i];
        counts[i].count = 0;
        counts[i].found = 0;
    }
    
    for (size_t i = 0; i < list->size; i++) {
        for (size_t j = 0; j < tuple->size; j++) {
            if (list->data[i] == tuple->data[j]) {
                counts[i].count++;
                counts[i].found = 1;
            }
        }
    }
    
    size_t unique_count = 0;
    for (size_t i = 0; i < list->size; i++) {
        int is_duplicate = 0;
        for (size_t j = 0; j < i; j++) {
            if (list->data[i] == list->data[j]) {
                is_duplicate = 1;
                break;
            }
        }
        if (!is_duplicate && counts[i].found) {
            unique_count++;
        } else if (is_duplicate) {
            counts[i].found = 0;
        }
    }
    
    ElementCount *unique_counts = NULL;
    if (unique_count > 0) {
        unique_counts = (ElementCount *)malloc(unique_count * sizeof(ElementCount));
        if (unique_counts == NULL) {
            free(counts);
            return;
        }
        
        size_t index = 0;
        for (size_t i = 0; i < list->size; i++) {
            if (counts[i].found) {
                unique_counts[index++] = counts[i];
            }
        }
    }
    
    free(counts);
    *result = unique_counts;
    *result_size = unique_count;
}

int main(void) {
    int list_data[] = {1, 2, 3, 4, 5};
    int tuple_data[] = {1, 2, 3, 2, 1, 4, 5, 5, 5, 1};
    
    List list;
    list.data = list_data;
    list.size = sizeof(list_data) / sizeof(list_data[0]);
    
    Tuple tuple;
    tuple.data = tuple_data;
    tuple.size = sizeof(tuple_data) / sizeof(tuple_data[0]);
    
    ElementCount *result = NULL;
    size_t result_size = 0;
    
    count_occurrences(&list, &tuple, &result, &result_size);
    
    for (size_t i = 0; i < result_size; i++) {
        printf("Element %d occurs %zu times\n", result[i].element, result[i].count);
    }
    
    if (result != NULL) {
        free(result);
    }
    
    return 0;
}