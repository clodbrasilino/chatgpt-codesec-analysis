#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void *entries;
    size_t count;
} Dictionary;

static Dictionary *create_empty_dictionaries(size_t count)
{
    if (count == 0 || count > SIZE_MAX / sizeof(Dictionary)) {
        return NULL;
    }

    return calloc(count, sizeof(Dictionary));
}

static void destroy_dictionaries(Dictionary *dictionaries, size_t count)
{
    if (dictionaries == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(dictionaries[i].entries);
        dictionaries[i].entries = NULL;
        dictionaries[i].count = 0;
    }

    free(dictionaries);
}

int main(void)
{
    const size_t count = 10;
    Dictionary *dictionaries = create_empty_dictionaries(count);

    if (dictionaries == NULL) {
        fputs("Failed to create dictionaries\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        printf("Dictionary %zu contains %zu entries at %p\n",
               i,
               dictionaries[i].count,
               dictionaries[i].entries);
    }

    destroy_dictionaries(dictionaries, count);
    return EXIT_SUCCESS;
}