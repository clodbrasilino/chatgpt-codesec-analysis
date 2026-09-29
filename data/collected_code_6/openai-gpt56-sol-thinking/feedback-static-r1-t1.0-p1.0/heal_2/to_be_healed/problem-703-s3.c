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

bool dictionary_contains(const Dictionary *dictionary, const char *key)
{
    size_t index;

    if (dictionary == NULL || key == NULL) {
        return false;
    }

    if (dictionary->count > 0U && dictionary->entries == NULL) {
        return false;
    }

    for (index = 0U; index < dictionary->count; ++index) {
        const char *entry_key = dictionary->entries[index].key;

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
        {"blue"},
        {"dog"}
    };
    const Dictionary dictionary = {
        entries,
        sizeof(entries) / sizeof(entries[0])
    };
    /* Possible weaknesses found:
     *  The scope of the variable 'program_name' can be reduced. [variableScope]
     */
    const char *program_name;
    bool present;

    if (argc != 2) {
        program_name = argc > 0 && argv[0] != NULL ? argv[0] : "program";

        if (fprintf(stderr, "Usage: %s <key>\n", program_name) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    present = dictionary_contains(&dictionary, argv[1]);

    if (printf("%s\n", present ? "present" : "not present") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}