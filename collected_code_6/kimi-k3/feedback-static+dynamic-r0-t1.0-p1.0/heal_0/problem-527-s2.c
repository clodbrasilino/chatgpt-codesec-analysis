#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int first;
    int second;
} Pair;

typedef struct {
    Pair *pairs;
    size_t count;
    size_t capacity;
} PairList;

int init_pair_list(PairList *list, size_t initial_capacity)
{
    if (list == NULL || initial_capacity == 0) {
        return -1;
    }
    
    list->pairs = malloc(initial_capacity * sizeof(Pair));
    if (list->pairs == NULL) {
        return -1;
    }
    
    list->count = 0;
    list->capacity = initial_capacity;
    return 0;
}

int add_pair(PairList *list, int first, int second)
{
    if (list == NULL) {
        return -1;
    }
    
    if (list->count >= list->capacity) {
        size_t new_capacity = list->capacity * 2;
        Pair *new_pairs = realloc(list->pairs, new_capacity * sizeof(Pair));
        if (new_pairs == NULL) {
            return -1;
        }
        list->pairs = new_pairs;
        list->capacity = new_capacity;
    }
    
    list->pairs[list->count].first = first;
    list->pairs[list->count].second = second;
    list->count++;
    return 0;
}

void free_pair_list(PairList *list)
{
    if (list != NULL && list->pairs != NULL) {
        free(list->pairs);
        list->pairs = NULL;
        list->count = 0;
        list->capacity = 0;
    }
}

int find_pairs_with_sum(const int *arr, size_t size, int target_sum, PairList *result)
{
    if (arr == NULL || result == NULL || size < 2) {
        return -1;
    }
    
    for (size_t i = 0; i < size - 1; i++) {
        for (size_t j = i + 1; j < size; j++) {
            if (arr[i] + arr[j] == target_sum) {
                if (add_pair(result, arr[i], arr[j]) != 0) {
                    return -1;
                }
            }
        }
    }
    
    return 0;
}

int main(void)
{
    int arr[] = {1, 5, 7, -1, 5, 3, 2, 8, 4};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int target_sum = 6;
    PairList result;
    
    if (init_pair_list(&result, 10) != 0) {
        fprintf(stderr, "Failed to initialize pair list\n");
        return EXIT_FAILURE;
    }
    
    if (find_pairs_with_sum(arr, size, target_sum, &result) != 0) {
        fprintf(stderr, "Failed to find pairs\n");
        free_pair_list(&result);
        return EXIT_FAILURE;
    }
    
    printf("Pairs with sum %d:\n", target_sum);
    for (size_t i = 0; i < result.count; i++) {
        printf("(%d, %d)\n", result.pairs[i].first, result.pairs[i].second);
    }
    
    free_pair_list(&result);
    return EXIT_SUCCESS;
}