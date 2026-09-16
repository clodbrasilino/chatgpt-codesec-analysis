#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int add_unique_key(ValueGroup *group, int key) {
    for (size_t i = 0; i < group->key_count; i++) {
        if (group->keys[i] == key) {
            return 1;
        }
    }

    if (group->key_count >= group->key_capacity) {
        size_t new_capacity = group->key_capacity == 0 ? 4 : group->key_capacity * 2;
        int *new_keys = realloc(group->keys, new_capacity * sizeof(int));
        if (!new_keys) {
            return 0;
        }
        group->keys = new_keys;
        group->key_capacity = new_capacity;
    }

    group->keys[group->key_count++] = key;
    return 1;
}

ValueGroup* count_unique_keys(const Tuple *tuples, size_t tuple_count, size_t *group_count_out) {
    if (!tuples || !group_count_out) {
        return NULL;
    }

    ValueGroup *groups = NULL;
    size_t group_count = 0;
    size_t group_capacity = 0;

    for (size_t i = 0; i < tuple_count; i++) {
        int current_value = tuples[i].value;
        int current_key = tuples[i].key;
        ValueGroup *target_group = NULL;

        for (size_t j = 0; j < group_count; j++) {
            if (groups[j].value == current_value) {
                target_group = &groups[j];
                break;
            }
        }

        if (!target_group) {
            if (group_count >= group_capacity) {
                size_t new_capacity = group_capacity == 0 ? 4 : group_capacity * 2;
                ValueGroup *new_groups = realloc(groups, new_capacity * sizeof(ValueGroup));
                if (!new_groups) {
                    for (size_t k = 0; k < group_count; k++) {
                        free(groups[k].keys);
                    }
                    free(groups);
                    return NULL;
                }
                groups = new_groups;
                group_capacity = new_capacity;
            }

            target_group = &groups[group_count++];
            target_group->value = current_value;
            target_group->keys = NULL;
            target_group->key_count = 0;
            target_group->key_capacity = 0;
        }

        if (!add_unique_key(target_group, current_key)) {
            for (size_t k = 0; k < group_count; k++) {
                free(groups[k].keys);
            }
            free(groups);
            return NULL;
        }
    }

    *group_count_out = group_count;
    return groups;
}

int main(void) {
    Tuple tuples[] = {
        {1, 10},
        {2, 10},
        {1, 10},
        {3, 20},
        {4, 20},
        {4, 20},
        {5, 30}
    };
    size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    size_t group_count = 0;

    ValueGroup *groups = count_unique_keys(tuples, tuple_count, &group_count);
    if (!groups) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (size_t i = 0; i < group_count; i++) {
        printf("Value: %d, Unique Keys Count: %zu\n", groups[i].value, groups[i].key_count);
        free(groups[i].keys);
    }
    free(groups);

    return 0;
}