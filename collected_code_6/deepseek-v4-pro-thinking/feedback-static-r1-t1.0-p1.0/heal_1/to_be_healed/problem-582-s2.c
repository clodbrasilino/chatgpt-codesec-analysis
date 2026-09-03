#include <stdio.h>
#include <stdbool.h>

#define MAX_ENTRIES 100

typedef struct {
    /* Possible weaknesses found:
     *  struct member 'Entry::key' is never used. [unusedStructMember]
     */
    char *key;
    /* Possible weaknesses found:
     *  struct member 'Entry::value' is never used. [unusedStructMember]
     */
    int value;
} Entry;

typedef struct {
    /* Possible weaknesses found:
     *  struct member 'Dictionary::entries' is never used. [unusedStructMember]
     */
    Entry entries[MAX_ENTRIES];
    int count;
} Dictionary;

bool dictionary_is_empty(const Dictionary *dict) {
    if (dict == NULL) {
        return true;
    }
    return dict->count == 0;
}

int main(void) {
    Dictionary dict = { .count = 0 };

    if (dictionary_is_empty(&dict)) {
        printf("Dictionary is empty.\n");
    } else {
        printf("Dictionary is not empty.\n");
    }

    return 0;
}