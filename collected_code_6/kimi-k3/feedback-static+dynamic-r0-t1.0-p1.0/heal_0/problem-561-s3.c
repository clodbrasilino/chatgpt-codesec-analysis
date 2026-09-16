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
} PairArray;

typedef struct {
    int key;
    int *values;
    size_t value_count;
    size_t value_capacity;
} PairGroup;

static int init_pair_array(PairArray *arr, size_t initial_capacity) {
    if (arr == NULL || initial_capacity == 0) {
        return -1;
    }
    arr->pairs = malloc(initial_capacity * sizeof(Pair));
    if (arr->pairs == NULL) {
        return -1;
    }
    arr->count = 0;
    arr->capacity = initial_capacity;
    return 0;
}

static void free_pair_array(PairArray *arr) {
    if (arr != NULL) {
        free(arr->pairs);
        arr->pairs = NULL;
        arr->count = 0;
        arr->capacity = 0;
    }
}

static int add_to_group(PairGroup *group, int value) {
    int *new_values;
    
    if (group->value_count >= group->value_capacity) {
        size_t new_capacity = (group->value_capacity == 0) ? 4 : group->value_capacity * 2;
        new_values = realloc(group->values, new_capacity * sizeof(int));
        if (new_values == NULL) {
            return -1;
        }
        group->values = new_values;
        group->value_capacity = new_capacity;
    }
    group->values[group->value_count++] = value;
    return 0;
}

static int find_group_index(PairGroup *groups, size_t group_count, int key) {
    size_t i;
    for (i = 0; i < group_count; i++) {
        if (groups[i].key == key) {
            return (int)i;
        }
    }
    return -1;
}

static int add_pair_to_groups(PairGroup **groups_ptr, size_t *group_count, size_t *group_capacity, Pair p) {
    int idx;
    PairGroup *new_groups;
    
    idx = find_group_index(*groups_ptr, *group_count, p.first);
    if (idx >= 0) {
        return add_to_group(&(*groups_ptr)[idx], p.second);
    }
    
    idx = find_group_index(*groups_ptr, *group_count, p.second);
    if (idx >= 0) {
        return add_to_group(&(*groups_ptr)[idx], p.first);
    }
    
    if (*group_count >= *group_capacity) {
        size_t new_capacity = (*group_capacity == 0) ? 4 : *group_capacity * 2;
        new_groups = realloc(*groups_ptr, new_capacity * sizeof(PairGroup));
        if (new_groups == NULL) {
            return -1;
        }
        *groups_ptr = new_groups;
        *group_capacity = new_capacity;
    }
    
    (*groups_ptr)[*group_count].key = p.first;
    (*groups_ptr)[*group_count].values = NULL;
    (*groups_ptr)[*group_count].value_count = 0;
    (*groups_ptr)[*group_count].value_capacity = 0;
    
    if (add_to_group(&(*groups_ptr)[*group_count], p.second) != 0) {
        return -1;
    }
    (*group_count)++;
    return 0;
}

static int assign_pair_elements(const Pair *input, size_t input_count, PairArray *result) {
    PairGroup *groups = NULL;
    size_t group_count = 0;
    size_t group_capacity = 0;
    size_t i, j;
    int ret = -1;
    
    if (input == NULL || result == NULL || input_count == 0) {
        return -1;
    }
    
    for (i = 0; i < input_count; i++) {
        if (add_pair_to_groups(&groups, &group_count, &group_capacity, input[i]) != 0) {
            goto cleanup;
        }
    }
    
    for (i = 0; i < group_count; i++) {
        for (j = 0; j < groups[i].value_count; j++) {
            if (result->count >= result->capacity) {
                size_t new_capacity = result->capacity * 2;
                Pair *new_pairs = realloc(result->pairs, new_capacity * sizeof(Pair));
                if (new_pairs == NULL) {
                    goto cleanup;
                }
                result->pairs = new_pairs;
                result->capacity = new_capacity;
            }
            result->pairs[result->count].first = groups[i].key;
            result->pairs[result->count].second = groups[i].values[j];
            result->count++;
        }
    }
    
    ret = 0;

cleanup:
    for (i = 0; i < group_count; i++) {
        free(groups[i].values);
    }
    free(groups);
    return ret;
}

int main(void) {
    Pair input[] = {{1, 2}, {3, 4}, {1, 5}, {3, 6}, {7, 8}};
    size_t input_count = sizeof(input) / sizeof(input[0]);
    PairArray result = {NULL, 0, 0};
    size_t i;
    
    if (init_pair_array(&result, 16) != 0) {
        fprintf(stderr, "Failed to initialize result array\n");
        return EXIT_FAILURE;
    }
    
    if (assign_pair_elements(input, input_count, &result) != 0) {
        fprintf(stderr, "Failed to assign pair elements\n");
        free_pair_array(&result);
        return EXIT_FAILURE;
    }
    
    printf("Input pairs: ");
    for (i = 0; i < input_count; i++) {
        printf("(%d, %d) ", input[i].first, input[i].second);
    }
    printf("\n\nAssigned pairs:\n");
    
    for (i = 0; i < result.count; i++) {
        printf("(%d, %d)\n", result.pairs[i].first, result.pairs[i].second);
    }
    
    free_pair_array(&result);
    return EXIT_SUCCESS;
}