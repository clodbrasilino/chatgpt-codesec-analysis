#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    size_t count;
} Dictionary;

bool all_dictionaries_empty(const Dictionary *dictionaries, size_t count) {
    if (dictionaries == NULL) {
        return count == 0;
    }
    for (size_t i = 0; i < count; ++i) {
        if (dictionaries[i].count != 0) {
            return false;
        }
    }
    return true;
}

static void print_bool(bool value) {
    printf("%s\n", value ? "true" : "false");
}

int main(void) {
    Dictionary dictionaries[3] = { {0} };

    print_bool(all_dictionaries_empty(dictionaries, 3));

    dictionaries[1].count = 1;
    print_bool(all_dictionaries_empty(dictionaries, 3));

    print_bool(all_dictionaries_empty(NULL, 0));
    print_bool(all_dictionaries_empty(NULL, 1));

    return 0;
}