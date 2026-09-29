#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Pair;

typedef struct {
    Pair *data;
    size_t size;
    size_t capacity;
} PairList;

int pair_list_init(PairList *list, size_t initial_capacity) {
    if (list == NULL || initial_capacity == 0) {
        return 0;
    }
    list->data = (Pair *)malloc(initial_capacity * sizeof(Pair));
    if (list->data == NULL) {
        return 0;
    }
    list->size = 0;
    list->capacity = initial_capacity;
    return 1;
}

void pair_list_free(PairList *list) {
    if (list != NULL) {
        free(list->data);
        list->data = NULL;
        list->size = 0;
        list->capacity = 0;
    }
}

int pair_list_add(PairList *list, int first, int second) {
    if (list == NULL) {
        return 0;
    }
    if (list->size >= list->capacity) {
        size_t new_capacity = list->capacity * 2;
        Pair *new_data = (Pair *)realloc(list->data, new_capacity * sizeof(Pair));
        if (new_data == NULL) {
            return 0;
        }
        list->data = new_data;
        list->capacity = new_capacity;
    }
    list->data[list->size].first = first;
    list->data[list->size].second = second;
    list->size++;
    return 1;
}

int extract_symmetric_pairs(const Pair *pairs, size_t count, PairList *result) {
    if (pairs == NULL || result == NULL || count == 0) {
        return 0;
    }
    if (!pair_list_init(result, count)) {
        return 0;
    }
    for (size_t i = 0; i < count; i++) {
        for (size_t j = i + 1; j < count; j++) {
            if (pairs[i].first == pairs[j].second && 
                pairs[i].second == pairs[j].first) {
                if (!pair_list_add(result, pairs[i].first, pairs[i].second)) {
                    pair_list_free(result);
                    return 0;
                }
                if (!pair_list_add(result, pairs[j].first, pairs[j].second)) {
                    pair_list_free(result);
                    return 0;
                }
            }
        }
    }
    return 1;
}

int main(void) {
    Pair pairs[] = {
        {11, 20},
        {30, 40},
        {5, 10},
        {40, 30},
        {10, 5}
    };
    size_t count = sizeof(pairs) / sizeof(pairs[0]);
    PairList result = {NULL, 0, 0};

    if (!extract_symmetric_pairs(pairs, count, &result)) {
        fprintf(stderr, "Error: Failed to extract symmetric pairs\n");
        return EXIT_FAILURE;
    }

    printf("Symmetric pairs:\n");
    for (size_t i = 0; i < result.size; i += 2) {
        printf("(%d, %d) and (%d, %d)\n", 
               result.data[i].first, result.data[i].second,
               result.data[i + 1].first, result.data[i + 1].second);
    }

    pair_list_free(&result);
    return EXIT_SUCCESS;
}