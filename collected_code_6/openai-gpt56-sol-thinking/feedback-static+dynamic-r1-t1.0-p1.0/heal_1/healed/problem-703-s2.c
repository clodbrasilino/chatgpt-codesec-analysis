#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *key;
} DictionaryEntry;

typedef struct {
    const DictionaryEntry *entries;
    size_t count;
} Dictionary;

static bool dictionary_contains(const Dictionary *dictionary, const char *key)
{
    if (dictionary == NULL || key == NULL) {
        return false;
    }

    if (dictionary->count > 0U && dictionary->entries == NULL) {
        return false;
    }

    for (size_t i = 0U; i < dictionary->count; ++i) {
        const char *entry_key = dictionary->entries[i].key;

        if (entry_key != NULL && strcmp(entry_key, key) == 0) {
            return true;
        }
    }

    return false;
}

int main(int argc, char *const argv[])
{
    static const DictionaryEntry entries[] = {
        {"apple"},
        {"carrot"},
        {"milk"}
    };

    const Dictionary dictionary = {
        entries,
        sizeof(entries) / sizeof(entries[0])
    };

    if (argc != 2) {
        const char *program_name =
            argc > 0 && argv[0] != NULL ? argv[0] : "program";

        fprintf(stderr, "Usage: %s <key>\n", program_name);
        return EXIT_FAILURE;
    }

    if (dictionary_contains(&dictionary, argv[1])) {
        puts("Key is present");
    } else {
        puts("Key is not present");
    }

    return EXIT_SUCCESS;
}