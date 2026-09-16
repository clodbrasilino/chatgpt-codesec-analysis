#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    int first;
    int second;
} Pair;

typedef struct {
    Pair *pairs;
    size_t count;
    size_t capacity;
} PairList;

static bool init_pair_list(PairList *list, size_t initial_capacity) {
    if (list == NULL) {
        return false;
    }
    list->pairs = NULL;
    list->count = 0;
    list->capacity = 0;
    
    if (initial_capacity == 0) {
        return true;
    }
    
    list->pairs = malloc(initial_capacity * sizeof(Pair));
    if (list->pairs == NULL) {
        return false;
    }
    list->capacity = initial_capacity;
    return true;
}

static bool add_pair(PairList *list, int a, int b) {
    if (list == NULL) {
        return false;
    }
    
    if (list->count >= list->capacity) {
        size_t new_capacity = (list->capacity == 0) ? 8 : list->capacity * 2;
        if (new_capacity > SIZE_MAX / sizeof(Pair)) {
            return false;
        }
        Pair *new_pairs = realloc(list->pairs, new_capacity * sizeof(Pair));
        if (new_pairs == NULL) {
            return false;
        }
        list->pairs = new_pairs;
        list->capacity = new_capacity;
    }
    
    list->pairs[list->count].first = a;
    list->pairs[list->count].second = b;
    list->count++;
    return true;
}

static void free_pair_list(PairList *list) {
    if (list != NULL) {
        free(list->pairs);
        list->pairs = NULL;
        list->count = 0;
        list->capacity = 0;
    }
}

static int compare_ints(const void *a, const void *b) {
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    return (ia > ib) - (ia < ib);
}

PairList *find_pairs_with_sum(const int *arr, size_t size, int target_sum) {
    if (arr == NULL || size == 0) {
        return NULL;
    }
    
    PairList *result = malloc(sizeof(PairList));
    if (result == NULL) {
        return NULL;
    }
    
    if (!init_pair_list(result, 8)) {
        free(result);
        return NULL;
    }
    
    int *sorted = malloc(size * sizeof(int));
    if (sorted == NULL) {
        free_pair_list(result);
        free(result);
        return NULL;
    }
    
    for (size_t i = 0; i < size; i++) {
        sorted[i] = arr[i];
    }
    
    qsort(sorted, size, sizeof(int), compare_ints);
    
    size_t left = 0;
    size_t right = size - 1;
    
    while (left < right) {
        int sum = sorted[left] + sorted[right];
        
        if (sum == target_sum) {
            if (!add_pair(result, sorted[left], sorted[right])) {
                free(sorted);
                free_pair_list(result);
                free(result);
                return NULL;
            }
            left++;
            if (right > 0) {
                right--;
            } else {
                break;
            }
        } else if (sum < target_sum) {
            left++;
        } else {
            if (right > 0) {
                right--;
            } else {
                break;
            }
        }
    }
    
    free(sorted);
    return result;
}

int main(void) {
    int arr[] = {1, 5, 7, -1, 5, 3, 2, 8, 4, 6};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int target = 6;
    
    PairList *result = find_pairs_with_sum(arr, size, target);
    if (result == NULL) {
        fprintf(stderr, "Error: Failed to find pairs\n");
        return EXIT_FAILURE;
    }
    
    printf("Pairs with sum %d:\n", target);
    for (size_t i = 0; i < result->count; i++) {
        printf("(%d, %d)\n", result->pairs[i].first, result->pairs[i].second);
    }
    
    free_pair_list(result);
    free(result);
    
    return EXIT_SUCCESS;
}