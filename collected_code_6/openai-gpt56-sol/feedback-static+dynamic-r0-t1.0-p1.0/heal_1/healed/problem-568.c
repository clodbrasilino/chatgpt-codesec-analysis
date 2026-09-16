#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void *entries;
    size_t size;
} Dictionary;

Dictionary *create_empty_dictionaries(size_t count)
{
    if (count == 0 || count > SIZE_MAX / sizeof(Dictionary)) {
        return NULL;
    }

    return calloc(count, sizeof(Dictionary));
}

int main(void)
{
    const size_t count = 5;
    Dictionary *dictionaries = create_empty_dictionaries(count);

    if (dictionaries == NULL) {
        fprintf(stderr, "Failed to create dictionary list\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        dictionaries[i].entries = NULL;
        dictionaries[i].size = 0;
    }

    free(dictionaries);

    return EXIT_SUCCESS;
}