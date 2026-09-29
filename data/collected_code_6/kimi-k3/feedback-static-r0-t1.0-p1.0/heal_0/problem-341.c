#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    size_t size;
    size_t capacity;
} IntSet;

typedef struct {
    int first;
    int second;
} Tuple;

static int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

static int set_init(IntSet *set, size_t initial_capacity) {
    if (set == NULL || initial_capacity == 0) return -1;
    set->elements = malloc(initial_capacity * sizeof(int));
    if (set->elements == NULL) return -1;
    set->size = 0;
    set->capacity = initial_capacity;
    return 0;
}

static void set_free(IntSet *set) {
    if (set != NULL) {
        free(set->elements);
        set->elements = NULL;
        set->size = 0;
        set->capacity = 0;
    }
}

static int set_add(IntSet *set, int value) {
    if (set == NULL) return -1;
    
    for (size_t i = 0; i < set->size; i++) {
        if (set->elements[i] == value) return 0;
    }
    
    if (set->size >= set->capacity) {
        size_t new_capacity = set->capacity * 2;
        if (new_capacity < set->capacity) return -1;
        int *new_elements = realloc(set->elements, new_capacity * sizeof(int));
        if (new_elements == NULL) return -1;
        set->elements = new_elements;
        set->capacity = new_capacity;
    }
    
    set->elements[set->size++] = value;
    return 0;
}

Tuple *set_to_ordered_tuples(const IntSet *set, size_t *tuple_count) {
    if (set == NULL || tuple_count == NULL) return NULL;
    if (set->size < 2) {
        *tuple_count = 0;
        return NULL;
    }
    
    int *sorted = malloc(set->size * sizeof(int));
    if (sorted == NULL) return NULL;
    
    memcpy(sorted, set->elements, set->size * sizeof(int));
    qsort(sorted, set->size, sizeof(int), compare_ints);
    
    size_t count = set->size / 2;
    Tuple *tuples = malloc(count * sizeof(Tuple));
    if (tuples == NULL) {
        free(sorted);
        return NULL;
    }
    
    for (size_t i = 0; i < count; i++) {
        tuples[i].first = sorted[i * 2];
        tuples[i].second = sorted[i * 2 + 1];
    }
    
    free(sorted);
    *tuple_count = count;
    return tuples;
}

int main(void) {
    IntSet set;
    size_t tuple_count = 0;
    Tuple *tuples = NULL;
    
    if (set_init(&set, 4) != 0) {
        fprintf(stderr, "Failed to initialize set\n");
        return EXIT_FAILURE;
    }
    
    if (set_add(&set, 5) != 0 || set_add(&set, 2) != 0 || 
        set_add(&set, 8) != 0 || set_add(&set, 1) != 0 ||
        set_add(&set, 9) != 0 || set_add(&set, 3) != 0) {
        fprintf(stderr, "Failed to add elements\n");
        set_free(&set);
        return EXIT_FAILURE;
    }
    
    tuples = set_to_ordered_tuples(&set, &tuple_count);
    if (tuples == NULL && tuple_count > 0) {
        fprintf(stderr, "Failed to convert set to tuples\n");
        set_free(&set);
        return EXIT_FAILURE;
    }
    
    printf("Ordered tuples:\n");
    for (size_t i = 0; i < tuple_count; i++) {
        printf("(%d, %d)\n", tuples[i].first, tuples[i].second);
    }
    
    free(tuples);
    set_free(&set);
    
    return EXIT_SUCCESS;
}