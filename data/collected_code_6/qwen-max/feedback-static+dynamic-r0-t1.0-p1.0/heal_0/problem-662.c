#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} DictionaryEntry;

static int compare(const void *a, const void *b) {
    return strcmp(((DictionaryEntry *)a)->key, ((DictionaryEntry *)b)->key);
}

void sort_dictionary(DictionaryEntry *list, size_t count) {
    qsort(list, count, sizeof(DictionaryEntry), compare);
}

int main() {
    DictionaryEntry entries[] = {
        {"banana", "yellow"},
        {"apple", "red"},
        {"cherry", "red"}
    };
    size_t num_entries = sizeof(entries) / sizeof(entries[0]);

    sort_dictionary(entries, num_entries);

    for (size_t i = 0; i < num_entries; i++) {
        printf("%s: %s\n", entries[i].key, entries[i].value);
    }

    return 0;
}