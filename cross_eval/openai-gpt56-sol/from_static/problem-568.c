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

    Dictionary *list = calloc(count, sizeof(Dictionary));
    if (list == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        list[i].entries = NULL;
        list[i].size = 0;
    }

    return list;
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
        printf("Dictionary %zu: entries=%p, size=%zu\n",
               i, dictionaries[i].entries, dictionaries[i].size);
    }

    free(dictionaries);
    return EXIT_SUCCESS;
}