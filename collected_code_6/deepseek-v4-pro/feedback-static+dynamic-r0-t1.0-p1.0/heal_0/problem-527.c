#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Pair;

typedef struct {
    Pair *pairs;
    int count;
    int capacity;
} PairList;

int init_pair_list(PairList *list) {
    if (list == NULL) return 0;
    list->count = 0;
    list->capacity = 10;
    list->pairs = (Pair *)malloc(list->capacity * sizeof(Pair));
    if (list->pairs == NULL) return 0;
    return 1;
}

int add_pair(PairList *list, int a, int b) {
    if (list == NULL || list->pairs == NULL) return 0;
    if (list->count >= list->capacity) {
        int new_capacity = list->capacity * 2;
        Pair *new_pairs = (Pair *)realloc(list->pairs, new_capacity * sizeof(Pair));
        if (new_pairs == NULL) return 0;
        list->pairs = new_pairs;
        list->capacity = new_capacity;
    }
    list->pairs[list->count].first = a;
    list->pairs[list->count].second = b;
    list->count++;
    return 1;
}

void free_pair_list(PairList *list) {
    if (list != NULL && list->pairs != NULL) {
        free(list->pairs);
        list->pairs = NULL;
        list->count = 0;
        list->capacity = 0;
    }
}

void find_pairs(int arr[], int n, int target, PairList *result) {
    if (arr == NULL || result == NULL || n <= 0) return;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] + arr[j] == target) {
                if (!add_pair(result, arr[i], arr[j])) {
                    return;
                }
            }
        }
    }
}

int main(void) {
    int arr[] = {1, 5, 7, -1, 5, 3, 3, 4, 8, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 8;
    PairList result;
    
    if (!init_pair_list(&result)) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    find_pairs(arr, n, target, &result);
    
    printf("Pairs with sum %d:\n", target);
    for (int i = 0; i < result.count; i++) {
        printf("(%d, %d)\n", result.pairs[i].first, result.pairs[i].second);
    }
    
    free_pair_list(&result);
    return 0;
}