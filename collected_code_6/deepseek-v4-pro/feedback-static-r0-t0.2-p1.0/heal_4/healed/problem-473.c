#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int *elements;
    int size;
} Tuple;

typedef struct {
    Tuple *tuples;
    int size;
} TupleList;

typedef struct {
    int *elements;
    int size;
    int capacity;
} IntArray;

static int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    return (arg1 > arg2) - (arg1 < arg2);
}

static void sort_tuple(Tuple *tuple) {
    if (tuple->size > 1) {
        qsort(tuple->elements, tuple->size, sizeof(int), compare_ints);
    }
}

static int tuples_equal(const Tuple *a, const Tuple *b) {
    if (a->size != b->size) return 0;
    for (int i = 0; i < a->size; i++) {
        if (a->elements[i] != b->elements[i]) return 0;
    }
    return 1;
}

static void init_int_array(IntArray *arr) {
    arr->elements = NULL;
    arr->size = 0;
    arr->capacity = 0;
}

static int append_to_int_array(IntArray *arr, int value) {
    if (arr->size >= arr->capacity) {
        int new_capacity = arr->capacity == 0 ? 8 : arr->capacity * 2;
        if (new_capacity <= 0 || (size_t)new_capacity > SIZE_MAX / sizeof(int)) {
            return 0;
        }
        int *new_elements = realloc(arr->elements, new_capacity * sizeof(int));
        if (new_elements == NULL) return 0;
        arr->elements = new_elements;
        arr->capacity = new_capacity;
    }
    arr->elements[arr->size++] = value;
    return 1;
}

static void free_int_array(IntArray *arr) {
    free(arr->elements);
    init_int_array(arr);
}

static int tuple_contains(const Tuple *tuple, int value) {
    for (int i = 0; i < tuple->size; i++) {
        if (tuple->elements[i] == value) return 1;
    }
    return 0;
}

static int build_intersection(const Tuple *t1, const Tuple *t2, Tuple *result) {
    IntArray temp;
    init_int_array(&temp);
    
    for (int i = 0; i < t1->size; i++) {
        Tuple check_tuple;
        check_tuple.elements = temp.elements;
        check_tuple.size = temp.size;
        if (tuple_contains(t2, t1->elements[i]) && !tuple_contains(&check_tuple, t1->elements[i])) {
            if (!append_to_int_array(&temp, t1->elements[i])) {
                free_int_array(&temp);
                return 0;
            }
        }
    }
    
    result->elements = temp.elements;
    result->size = temp.size;
    return 1;
}

static void free_tuple(Tuple *tuple) {
    free(tuple->elements);
    tuple->elements = NULL;
    tuple->size = 0;
}

static void free_tuple_list(TupleList *list) {
    if (list == NULL) return;
    for (int i = 0; i < list->size; i++) {
        free_tuple(&list->tuples[i]);
    }
    free(list->tuples);
    list->tuples = NULL;
    list->size = 0;
}

static int safe_memcpy(void *dest, size_t dest_size, const void *src, size_t src_size) {
    if (dest == NULL || src == NULL) return 0;
    if (src_size > dest_size) return 0;
    if (src_size > SIZE_MAX / 2) return 0;
    if (dest_size < src_size) return 0;
    if (src_size == 0) return 1;
    
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;
    size_t i = 0;
    while (i < src_size) {
        d[i] = s[i];
        i++;
    }
    return 1;
}

TupleList tuple_intersection(TupleList *list) {
    TupleList result;
    result.tuples = NULL;
    result.size = 0;
    
    if (list == NULL || list->size <= 0) {
        return result;
    }
    
    if (list->size > SIZE_MAX / sizeof(Tuple)) {
        return result;
    }
    
    Tuple *sorted_tuples = malloc((size_t)list->size * sizeof(Tuple));
    if (sorted_tuples == NULL) {
        return result;
    }
    
    for (int i = 0; i < list->size; i++) {
        sorted_tuples[i].elements = NULL;
        sorted_tuples[i].size = 0;
    }
    
    for (int i = 0; i < list->size; i++) {
        if (list->tuples[i].size < 0) {
            for (int j = 0; j < i; j++) {
                free_tuple(&sorted_tuples[j]);
            }
            free(sorted_tuples);
            return result;
        }
        if (list->tuples[i].size > 0 && (size_t)list->tuples[i].size > SIZE_MAX / sizeof(int)) {
            for (int j = 0; j < i; j++) {
                free_tuple(&sorted_tuples[j]);
            }
            free(sorted_tuples);
            return result;
        }
        
        size_t alloc_size = (size_t)list->tuples[i].size * sizeof(int);
        sorted_tuples[i].elements = malloc(alloc_size);
        if (sorted_tuples[i].elements == NULL) {
            for (int j = 0; j < i; j++) {
                free_tuple(&sorted_tuples[j]);
            }
            free(sorted_tuples);
            return result;
        }
        sorted_tuples[i].size = list->tuples[i].size;
        
        if (list->tuples[i].size > 0) {
            if (!safe_memcpy(sorted_tuples[i].elements, alloc_size, 
                            list->tuples[i].elements, alloc_size)) {
                for (int j = 0; j <= i; j++) {
                    free_tuple(&sorted_tuples[j]);
                }
                free(sorted_tuples);
                return result;
            }
        }
        sort_tuple(&sorted_tuples[i]);
    }
    
    Tuple *unique_tuples = malloc((size_t)list->size * sizeof(Tuple));
    if (unique_tuples == NULL) {
        for (int i = 0; i < list->size; i++) {
            free_tuple(&sorted_tuples[i]);
        }
        free(sorted_tuples);
        return result;
    }
    
    for (int i = 0; i < list->size; i++) {
        unique_tuples[i].elements = NULL;
        unique_tuples[i].size = 0;
    }
    
    int unique_count = 0;
    for (int i = 0; i < list->size; i++) {
        int is_duplicate = 0;
        for (int j = 0; j < unique_count; j++) {
            if (tuples_equal(&sorted_tuples[i], &unique_tuples[j])) {
                is_duplicate = 1;
                break;
            }
        }
        if (!is_duplicate) {
            if (sorted_tuples[i].size < 0) {
                for (int j = 0; j < unique_count; j++) {
                    free_tuple(&unique_tuples[j]);
                }
                for (int j = 0; j < list->size; j++) {
                    free_tuple(&sorted_tuples[j]);
                }
                free(sorted_tuples);
                free(unique_tuples);
                return result;
            }
            if (sorted_tuples[i].size > 0 && (size_t)sorted_tuples[i].size > SIZE_MAX / sizeof(int)) {
                for (int j = 0; j < unique_count; j++) {
                    free_tuple(&unique_tuples[j]);
                }
                for (int j = 0; j < list->size; j++) {
                    free_tuple(&sorted_tuples[j]);
                }
                free(sorted_tuples);
                free(unique_tuples);
                return result;
            }
            
            size_t alloc_size = (size_t)sorted_tuples[i].size * sizeof(int);
            unique_tuples[unique_count].elements = malloc(alloc_size);
            if (unique_tuples[unique_count].elements == NULL) {
                for (int j = 0; j < unique_count; j++) {
                    free_tuple(&unique_tuples[j]);
                }
                for (int j = 0; j < list->size; j++) {
                    free_tuple(&sorted_tuples[j]);
                }
                free(sorted_tuples);
                free(unique_tuples);
                return result;
            }
            unique_tuples[unique_count].size = sorted_tuples[i].size;
            
            if (sorted_tuples[i].size > 0) {
                if (!safe_memcpy(unique_tuples[unique_count].elements, alloc_size,
                                sorted_tuples[i].elements, alloc_size)) {
                    free(unique_tuples[unique_count].elements);
                    unique_tuples[unique_count].elements = NULL;
                    for (int j = 0; j < unique_count; j++) {
                        free_tuple(&unique_tuples[j]);
                    }
                    for (int j = 0; j < list->size; j++) {
                        free_tuple(&sorted_tuples[j]);
                    }
                    free(sorted_tuples);
                    free(unique_tuples);
                    return result;
                }
            }
            unique_count++;
        }
    }
    
    for (int i = 0; i < list->size; i++) {
        free_tuple(&sorted_tuples[i]);
    }
    free(sorted_tuples);
    
    if (unique_count == 0) {
        free(unique_tuples);
        return result;
    }
    
    Tuple current = unique_tuples[0];
    Tuple next;
    int success = 1;
    int current_owned = 0;
    
    for (int i = 1; i < unique_count; i++) {
        if (!build_intersection(&current, &unique_tuples[i], &next)) {
            success = 0;
            break;
        }
        if (current_owned) {
            free_tuple(&current);
        }
        current = next;
        current_owned = 1;
    }
    
    if (unique_count == 1) {
        current = unique_tuples[0];
        current_owned = 0;
    }
    
    for (int i = 0; i < unique_count; i++) {
        if (unique_count == 1 || (current_owned && i == 0)) {
            continue;
        }
        free_tuple(&unique_tuples[i]);
    }
    free(unique_tuples);
    
    if (!success) {
        if (current_owned) {
            free_tuple(&current);
        }
        return result;
    }
    
    if (current.size > 0) {
        result.tuples = malloc(sizeof(Tuple));
        if (result.tuples == NULL) {
            if (current_owned) {
                free_tuple(&current);
            }
            return result;
        }
        result.tuples[0] = current;
        result.size = 1;
    } else {
        if (current_owned) {
            free_tuple(&current);
        }
    }
    
    return result;
}

int main(void) {
    int t1_elems[] = {1, 2, 3, 4};
    int t2_elems[] = {3, 4, 5, 6};
    int t3_elems[] = {4, 3, 7, 8};
    int t4_elems[] = {3, 4, 9, 10};
    
    Tuple tuples[4];
    tuples[0].elements = t1_elems;
    tuples[0].size = 4;
    tuples[1].elements = t2_elems;
    tuples[1].size = 4;
    tuples[2].elements = t3_elems;
    tuples[2].size = 4;
    tuples[3].elements = t4_elems;
    tuples[3].size = 4;
    
    TupleList list;
    list.tuples = tuples;
    list.size = 4;
    
    TupleList result = tuple_intersection(&list);
    
    if (result.size > 0) {
        printf("Intersection: ");
        for (int i = 0; i < result.tuples[0].size; i++) {
            printf("%d ", result.tuples[0].elements[i]);
        }
        printf("\n");
        free_tuple_list(&result);
    } else {
        printf("No intersection found\n");
    }
    
    return 0;
}