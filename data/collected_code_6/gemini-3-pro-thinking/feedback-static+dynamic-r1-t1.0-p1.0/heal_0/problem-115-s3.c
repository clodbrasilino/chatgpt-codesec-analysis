#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char **keys;
    char **values;
    size_t size;
} Dictionary;

bool are_all_dictionaries_empty(const Dictionary *dicts, size_t count) {
    if (dicts == NULL) {
        return count == 0;
    }

    for (size_t i = 0; i < count; ++i) {
        if (dicts[i].size > 0) {
            return false;
        }
    }

    return true;
}

int main(void) {
    size_t dict_count = 5;
    
    Dictionary *dicts = calloc(dict_count, sizeof(Dictionary));
    if (dicts == NULL) {
        return EXIT_FAILURE;
    }

    bool all_empty = are_all_dictionaries_empty(dicts, dict_count);

    if (all_empty) {
        printf("All dictionaries are empty.\n");
    } else {
        printf("Not all dictionaries are empty.\n");
    }

    free(dicts);

    return EXIT_SUCCESS;
}