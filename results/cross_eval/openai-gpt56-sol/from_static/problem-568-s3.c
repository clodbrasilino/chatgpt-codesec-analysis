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

    Dictionary *dictionaries = calloc(count, sizeof(Dictionary));

    if (dictionaries != NULL) {
        for (size_t i = 0; i < count; ++i) {
            dictionaries[i].entries = NULL;
            dictionaries[i].count = 0;
        }
    }

    return dictionaries;
}

static void destroy_dictionaries(Dictionary *dictionaries, size_t count)
{
    if (dictionaries == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(dictionaries[i].entries);
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

    printf("Created %zu empty dictionaries\n", count);

    destroy_dictionaries(dictionaries, count);
    return EXIT_SUCCESS;
}