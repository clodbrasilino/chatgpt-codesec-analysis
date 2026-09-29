#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *key;
    /* Possible weaknesses found:
     *  struct member 'DictionaryEntry::value' is never used. [unusedStructMember]
     */
    const char *value;
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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    static const DictionaryEntry entries[] = {
        {"apple", "fruit"},
        {"carrot", "vegetable"},
        {"blue", "color"},
        {"dog", "animal"}
    };
    const Dictionary dictionary = {
        entries,
        sizeof(entries) / sizeof(entries[0])
    };
    bool present;

    if (argc != 2) {
        if (fprintf(stderr, "Usage: %s <key>\n", argv[0]) < 0) {
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