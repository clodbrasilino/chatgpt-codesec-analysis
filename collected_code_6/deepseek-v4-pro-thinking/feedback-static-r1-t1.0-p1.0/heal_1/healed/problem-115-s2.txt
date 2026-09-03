#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    size_t count;
} Dictionary;

bool all_dictionaries_empty(const Dictionary *dictionaries, size_t count) {
    if (count == 0) {
        return true;
    }
    if (dictionaries == NULL) {
        return false;
    }
    for (size_t i = 0; i < count; ++i) {
        if (dictionaries[i].count != 0) {
            return false;
        }
    }
    return true;
}

int main(void) {
    Dictionary dictionaries[3] = { {0} };
    const Dictionary *null_dictionaries = NULL;
    size_t zero = 0;
    size_t one = 1;

    printf("%s\n", all_dictionaries_empty(dictionaries, 3) ? "true" : "false");

    dictionaries[1].count = 1;
    printf("%s\n", all_dictionaries_empty(dictionaries, 3) ? "true" : "false");

    printf("%s\n", all_dictionaries_empty(null_dictionaries, zero) ? "true" : "false");
    printf("%s\n", all_dictionaries_empty(null_dictionaries, one) ? "true" : "false");

    return 0;
}