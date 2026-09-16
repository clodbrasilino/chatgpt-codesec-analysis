#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct DictionaryEntry {
    /* Possible weaknesses found:
     *  struct member 'DictionaryEntry::key' is never used. [unusedStructMember]
     */
    const char *key;
    /* Possible weaknesses found:
     *  struct member 'DictionaryEntry::value' is never used. [unusedStructMember]
     */
    const char *value;
    /* Possible weaknesses found:
     *  struct member 'DictionaryEntry::next' is never used. [unusedStructMember]
     */
    struct DictionaryEntry *next;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *head;
} Dictionary;

typedef enum {
    DICTIONARY_SUCCESS = 0,
    DICTIONARY_INVALID_ARGUMENT
} DictionaryStatus;

static DictionaryStatus dictionary_is_empty(const Dictionary *dictionary,
                                            bool *is_empty)
{
    if (dictionary == NULL || is_empty == NULL) {
        return DICTIONARY_INVALID_ARGUMENT;
    }

    *is_empty = dictionary->head == NULL;
    return DICTIONARY_SUCCESS;
}

int main(void)
{
    Dictionary dictionary = { .head = NULL };
    bool is_empty = false;

    if (dictionary_is_empty(&dictionary, &is_empty) != DICTIONARY_SUCCESS) {
        fputs("Failed to check dictionary state.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(is_empty ? "Dictionary is empty." : "Dictionary is not empty.");
    return EXIT_SUCCESS;
}