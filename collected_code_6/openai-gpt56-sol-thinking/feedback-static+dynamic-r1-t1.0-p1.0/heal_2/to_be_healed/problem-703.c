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

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char *argv[const])
{
    static const DictionaryEntry entries[] = {
        {"apple"},
        {"carrot"},
        {"blue"}
    };

    const Dictionary dictionary = {
        entries,
        sizeof(entries) / sizeof(entries[0])
    };

    if (argc != 2 || argv[1] == NULL) {
        const char *program_name =
            argc > 0 && argv[0] != NULL ? argv[0] : "program";

        if (fprintf(stderr, "Usage: %s <key>\n", program_name) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    const bool is_present = dictionary_contains(&dictionary, argv[1]);

    if (printf("%s\n", is_present ? "present" : "not present") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}