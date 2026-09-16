#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} Dictionary;

static int compare_dictionaries(const void *left, const void *right)
{
    const Dictionary *a = left;
    const Dictionary *b = right;
    int result;

    result = strcmp(a->key, b->key);
    if (result != 0) {
        return result;
    }

    return strcmp(a->value, b->value);
}

static int sort_dictionaries(Dictionary *dictionaries, size_t count)
{
    if (dictionaries == NULL && count != 0U) {
        return -1;
    }

    if (count > 1U) {
        qsort(dictionaries, count, sizeof(*dictionaries), compare_dictionaries);
    }

    return 0;
}

int main(void)
{
    Dictionary dictionaries[] = {
        {"language", "C"},
        {"name", "Alice"},
        {"city", "London"},
        {"name", "Bob"}
    };
    const size_t count = sizeof(dictionaries) / sizeof(dictionaries[0]);

    if (sort_dictionaries(dictionaries, count) != 0) {
        fputs("Unable to sort dictionaries.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (printf("%s: %s\n", dictionaries[i].key, dictionaries[i].value) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}