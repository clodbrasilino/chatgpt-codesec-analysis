#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *key;
} DictionaryEntry;

typedef struct {
    const DictionaryEntry *entries;
    size_t size;
} Dictionary;

static bool dictionary_contains(const Dictionary *dictionary, const char *key)
{
    if (dictionary == NULL || key == NULL) {
        return false;
    }

    for (size_t i = 0; i < dictionary->size; ++i) {
        const char *entry_key = dictionary->entries[i].key;

        if (entry_key != NULL && strcmp(entry_key, key) == 0) {
            return true;
        }
    }

    return false;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <key>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const DictionaryEntry entries[] = {
        {"name"},
        {"age"},
        {"city"}
    };

    const Dictionary dictionary = {
        entries,
        sizeof entries / sizeof entries[0]
    };

    puts(dictionary_contains(&dictionary, argv[1])
             ? "Key is present"
             : "Key is not present");

    return EXIT_SUCCESS;
}