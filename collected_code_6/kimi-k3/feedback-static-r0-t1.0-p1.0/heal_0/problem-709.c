#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int value;
} Tuple;

typedef struct {
    int value;
    int *keys;
    size_t key_count;
    size_t key_capacity;
} ValueGroup;

static int key_exists(const int *keys, size_t count, int key)
{
    size_t i;
    for (i = 0; i < count; i++) {
        if (keys[i] == key) {
            return 1;
        }
    }
    return 0;
}

static int find_value_group(const ValueGroup *groups, size_t count, int value)
{
    size_t i;
    for (i = 0; i < count; i++) {
        if (groups[i].value == value) {
            return (int)i;
        }
    }
    return -1;
}

static void free_groups(ValueGroup *groups, size_t count)
{
    size_t i;
    if (groups != NULL) {
        for (i = 0; i < count; i++) {
            free(groups[i].keys);
        }
        free(groups);
    }
}

static ValueGroup *count_unique_keys(const Tuple *tuples, size_t tuple_count, size_t *result_count)
{
    ValueGroup *groups;
    size_t group_count;
    size_t group_capacity;
    size_t i;
    int group_index;

    if (tuples == NULL || result_count == NULL || tuple_count == 0) {
        if (result_count != NULL) {
            *result_count = 0;
        }
        return NULL;
    }

    group_capacity = 8;
    group_count = 0;
    groups = (ValueGroup *)calloc(group_capacity, sizeof(ValueGroup));
    if (groups == NULL) {
        *result_count = 0;
        return NULL;
    }

    for (i = 0; i < tuple_count; i++) {
        group_index = find_value_group(groups, group_count, tuples[i].value);

        if (group_index == -1) {
            if (group_count == group_capacity) {
                ValueGroup *new_groups;
                size_t new_capacity = group_capacity * 2;
                new_groups = (ValueGroup *)realloc(groups, new_capacity * sizeof(ValueGroup));
                if (new_groups == NULL) {
                    free_groups(groups, group_count);
                    *result_count = 0;
                    return NULL;
                }
                groups = new_groups;
                group_capacity = new_capacity;
            }

            groups[group_count].value = tuples[i].value;
            groups[group_count].key_count = 0;
            groups[group_count].key_capacity = 4;
            groups[group_count].keys = (int *)malloc(groups[group_count].key_capacity * sizeof(int));
            if (groups[group_count].keys == NULL) {
                free_groups(groups, group_count + 1);
                *result_count = 0;
                return NULL;
            }
            group_index = (int)group_count;
            group_count++;
        }

        if (!key_exists(groups[group_index].keys, groups[group_index].key_count, tuples[i].key)) {
            if (groups[group_index].key_count == groups[group_index].key_capacity) {
                int *new_keys;
                size_t new_capacity = groups[group_index].key_capacity * 2;
                new_keys = (int *)realloc(groups[group_index].keys, new_capacity * sizeof(int));
                if (new_keys == NULL) {
                    free_groups(groups, group_count);
                    *result_count = 0;
                    return NULL;
                }
                groups[group_index].keys = new_keys;
                groups[group_index].key_capacity = new_capacity;
            }
            groups[group_index].keys[groups[group_index].key_count] = tuples[i].key;
            groups[group_index].key_count++;
        }
    }

    *result_count = group_count;
    return groups;
}

int main(void)
{
    Tuple tuples[] = {
        {1, 100},
        {2, 100},
        {1, 100},
        {3, 200},
        {4, 200},
        {3, 200},
        {5, 300},
        {1, 100},
        {6, 300}
    };
    size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    size_t result_count = 0;
    size_t i;
    ValueGroup *results;

    results = count_unique_keys(tuples, tuple_count, &result_count);
    if (results == NULL && result_count == 0 && tuple_count > 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < result_count; i++) {
        printf("Value %d: %zu unique key(s)\n", results[i].value, results[i].key_count);
    }

    free_groups(results, result_count);
    return EXIT_SUCCESS;
}