#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

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

bool dictionary_key_at(const Dictionary *dictionary, size_t index, const char **key)
{
    if (dictionary == NULL || key == NULL || dictionary->entries == NULL) {
        return false;
    }

    if (index >= dictionary->count) {
        return false;
    }

    *key = dictionary->entries[index].key;
    return *key != NULL;
}

int main(void)
{
    static const DictionaryEntry entries[] = {
        {"name", "Alice"},
        {"age", "30"},
        {"city", "London"}
    };
    const Dictionary dictionary = {
        entries,
        sizeof(entries) / sizeof(entries[0])
    };
    const char *key = NULL;
    const size_t index = 1U;

    if (!dictionary_key_at(&dictionary, index, &key)) {
        if (fputs("Unable to access dictionary key\n", stderr) == EOF) {
            return 2;
        }
        return 1;
    }

    if (printf("%s\n", key) < 0) {
        return 2;
    }

    return 0;
}