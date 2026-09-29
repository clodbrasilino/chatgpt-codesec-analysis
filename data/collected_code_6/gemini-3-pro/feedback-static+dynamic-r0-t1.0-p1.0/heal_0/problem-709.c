#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} Tuple;

typedef struct {
    char *value;
    char **keys;
    size_t key_count;
    size_t key_capacity;
} ValueGroup;

ValueGroup* add_key_to_value_group(ValueGroup *groups, size_t *num_groups, const char *key, const char *value) {
    for (size_t i = 0; i < *num_groups; i++) {
        if (strcmp(groups[i].value, value) == 0) {
            for (size_t j = 0; j < groups[i].key_count; j++) {
                if (strcmp(groups[i].keys[j], key) == 0) {
                    return groups;
                }
            }
            if (groups[i].key_count >= groups[i].key_capacity) {
                size_t new_capacity = groups[i].key_capacity == 0 ? 4 : groups[i].key_capacity * 2;
                char **new_keys = realloc(groups[i].keys, new_capacity * sizeof(char *));
                if (!new_keys) {
                    return NULL; 
                }
                groups[i].keys = new_keys;
                groups[i].key_capacity = new_capacity;
            }
            char *new_key = strdup(key);
            if (!new_key) return NULL;
            groups[i].keys[groups[i].key_count++] = new_key;
            return groups;
        }
    }

    ValueGroup *new_groups = realloc(groups, (*num_groups + 1) * sizeof(ValueGroup));
    if (!new_groups) return NULL;
    groups = new_groups;

    groups[*num_groups].value = strdup(value);
    if (!groups[*num_groups].value) return NULL;
    
    groups[*num_groups].key_capacity = 4;
    groups[*num_groups].keys = malloc(groups[*num_groups].key_capacity * sizeof(char *));
    if (!groups[*num_groups].keys) {
        free(groups[*num_groups].value);
        return NULL;
    }
    
    char *new_key = strdup(key);
    if (!new_key) {
        free(groups[*num_groups].keys);
        free(groups[*num_groups].value);
        return NULL;
    }
    
    groups[*num_groups].keys[0] = new_key;
    groups[*num_groups].key_count = 1;
    (*num_groups)++;

    return groups;
}

void count_unique_keys_per_value(const Tuple *tuples, size_t num_tuples) {
    if (!tuples || num_tuples == 0) return;

    ValueGroup *groups = NULL;
    size_t num_groups = 0;

    for (size_t i = 0; i < num_tuples; i++) {
        if (!tuples[i].key || !tuples[i].value) continue;
        ValueGroup *new_groups = add_key_to_value_group(groups, &num_groups, tuples[i].key, tuples[i].value);
        if (!new_groups) {
            for (size_t j = 0; j < num_groups; j++) {
                for (size_t k = 0; k < groups[j].key_count; k++) {
                    free(groups[j].keys[k]);
                }
                free(groups[j].keys);
                free(groups[j].value);
            }
            free(groups);
            return;
        }
        groups = new_groups;
    }

    for (size_t i = 0; i < num_groups; i++) {
        printf("Value: %s, Unique Keys: %zu\n", groups[i].value, groups[i].key_count);
    }

    for (size_t i = 0; i < num_groups; i++) {
        for (size_t j = 0; j < groups[i].key_count; j++) {
            free(groups[i].keys[j]);
        }
        free(groups[i].keys);
        free(groups[i].value);
    }
    free(groups);
}

int main(void) {
    Tuple tuples[] = {
        {"k1", "v1"},
        {"k2", "v1"},
        {"k1", "v1"},
        {"k3", "v2"},
        {"k4", "v2"},
        {"k5", "v3"}
    };
    size_t num_tuples = sizeof(tuples) / sizeof(tuples[0]);

    count_unique_keys_per_value(tuples, num_tuples);

    return 0;
}