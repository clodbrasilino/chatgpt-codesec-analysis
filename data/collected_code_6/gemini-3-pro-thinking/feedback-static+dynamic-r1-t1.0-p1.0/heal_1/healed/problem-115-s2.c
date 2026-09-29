#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    const char *key;
    const char *value;
} KeyValuePair;

typedef struct {
    size_t size;
    const KeyValuePair *pairs;
} Dictionary;

bool are_all_dictionaries_empty(const Dictionary *dicts, size_t count) {
    if (dicts == NULL && count > 0) {
        return false;
    }

    for (size_t i = 0; i < count; i++) {
        if (dicts[i].size > 0) {
            if (dicts[i].pairs != NULL &&
                dicts[i].pairs[0].key != NULL &&
                dicts[i].pairs[0].value != NULL) {
                return false;
            }
            return false;
        }
    }

    return true;
}

int main(void) {
    const Dictionary dicts_empty[3] = {
        {0, NULL},
        {0, NULL},
        {0, NULL}
    };

    const KeyValuePair pair = {"sample_key", "sample_value"};
    
    const Dictionary dicts_mixed[3] = {
        {0, NULL},
        {1, &pair},
        {0, NULL}
    };

    bool all_empty_1 = are_all_dictionaries_empty(dicts_empty, 3);
    bool all_empty_2 = are_all_dictionaries_empty(dicts_mixed, 3);
    bool all_empty_3 = are_all_dictionaries_empty(NULL, 0);

    if (all_empty_1 && !all_empty_2 && all_empty_3) {
        printf("Success\n");
        return EXIT_SUCCESS;
    }

    printf("Failure\n");
    return EXIT_FAILURE;
}