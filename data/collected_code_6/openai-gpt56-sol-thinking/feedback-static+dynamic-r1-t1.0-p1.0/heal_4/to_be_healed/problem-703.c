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

    if (dictionary->entries == NULL) {
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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[])
{
    static const DictionaryEntry entries[] = {
        { .key = "apple" },
        { .key = "carrot" },
        { .key = "blue" }
    };

    const Dictionary dictionary = {
        .entries = entries,
        .count = sizeof entries / sizeof entries[0]
    };

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        const char *program_name = "program";

        if (argv != NULL && argc > 0 && argv[0] != NULL) {
            program_name = argv[0];
        }

        if (fputs("Usage: ", stderr) == EOF ||
            fputs(program_name, stderr) == EOF ||
            fputs(" <key>\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    const bool is_present = dictionary_contains(&dictionary, argv[1]);

    if (fputs(is_present ? "present\n" : "not present\n", stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}