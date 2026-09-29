#include <stdio.h>
#include <stddef.h>

typedef struct {
    int value;
} Entry;

typedef struct {
    Entry *entries;
    size_t size;
} Dictionary;

int all_values_same(const Dictionary *dict) {
    if (dict == NULL) {
        return -1;
    }
    if (dict->size == 0) {
        return 1;
    }
    if (dict->entries == NULL) {
        return -1;
    }

    int first_value = dict->entries[0].value;
    for (size_t i = 1; i < dict->size; i++) {
        if (dict->entries[i].value != first_value) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    Entry same_entries[] = {
        {42},
        {42},
        {42}
    };
    Dictionary same_dict = { same_entries, sizeof(same_entries) / sizeof(same_entries[0]) };

    Entry diff_entries[] = {
        {1},
        {2},
        {3}
    };
    Dictionary diff_dict = { diff_entries, sizeof(diff_entries) / sizeof(diff_entries[0]) };

    printf("%d\n", all_values_same(&same_dict));
    printf("%d\n", all_values_same(&diff_dict));
    printf("%d\n", all_values_same(NULL));

    return 0;
}