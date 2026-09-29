#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *key;
} DictionaryEntry;

static bool dictionary_contains(const DictionaryEntry *dictionary,
                                size_t entry_count,
                                const char *key)
{
    if (dictionary == NULL || key == NULL) {
        return false;
    }

    for (size_t i = 0; i < entry_count; ++i) {
        if (dictionary[i].key != NULL &&
            strcmp(dictionary[i].key, key) == 0) {
            return true;
        }
    }

    return false;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    static const DictionaryEntry dictionary[] = {
        {"apple"},
        {"carrot"},
        {"salmon"}
    };
    const size_t entry_count = sizeof dictionary / sizeof dictionary[0];

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <key>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (dictionary_contains(dictionary, entry_count, argv[1])) {
        printf("Key \"%s\" is present.\n", argv[1]);
    } else {
        printf("Key \"%s\" is not present.\n", argv[1]);
    }

    return EXIT_SUCCESS;
}