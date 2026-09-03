#include <stdio.h>
#include <stddef.h>

typedef struct Dictionary Dictionary;

typedef enum {
    TYPE_INT,
    TYPE_DICT
} ValueType;

typedef struct Entry {
    const char *key;
    ValueType type;
    union {
        int int_value;
        Dictionary *dict_value;
    } value;
} Entry;

struct Dictionary {
    Entry *entries;
    size_t count;
};

int dictionary_depth(const Dictionary *dict) {
    int max_child_depth;
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'entry' can be reduced. [variableScope]
     */
    const Entry *entry;

    if (dict == NULL) {
        return 0;
    }
    if (dict->entries == NULL) {
        return 1;
    }

    max_child_depth = 0;

    for (i = 0; i < dict->count; ++i) {
        entry = &dict->entries[i];

        if (entry->type == TYPE_DICT && entry->value.dict_value != NULL) {
            int child_depth = dictionary_depth(entry->value.dict_value);

            if (child_depth > max_child_depth) {
                max_child_depth = child_depth;
            }
        }
    }

    return max_child_depth + 1;
}

int main(void) {
    Entry inner_entries[2];
    Entry outer_entries[2];
    Dictionary inner;
    Dictionary outer;

    inner_entries[0].key = "a";
    inner_entries[0].type = TYPE_INT;
    inner_entries[0].value.int_value = 1;

    inner_entries[1].key = "b";
    inner_entries[1].type = TYPE_INT;
    inner_entries[1].value.int_value = 2;

    inner.entries = inner_entries;
    inner.count = 2;

    outer_entries[0].key = "nested";
    outer_entries[0].type = TYPE_DICT;
    outer_entries[0].value.dict_value = &inner;

    outer_entries[1].key = "x";
    outer_entries[1].type = TYPE_INT;
    outer_entries[1].value.int_value = 3;

    outer.entries = outer_entries;
    outer.count = 2;

    printf("%d\n", dictionary_depth(&outer));

    return 0;
}