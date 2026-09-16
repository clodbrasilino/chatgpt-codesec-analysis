#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *word;
    int count;
} WordEntry;

char *get_most_frequent_word(char **strings, size_t num_strings) {
    WordEntry *entries = NULL;
    size_t entry_count = 0;
    size_t entry_capacity = 0;
    char *result = NULL;

    if (strings == NULL || num_strings == 0) {
        return NULL;
    }

    for (size_t i = 0; i < num_strings; i++) {
        if (strings[i] == NULL) {
            continue;
        }

        char *str_copy = strdup(strings[i]);
        if (str_copy == NULL) {
            goto cleanup;
        }

        char *token = strtok(str_copy, " \t\n\r");
        while (token != NULL) {
            int found = 0;
            for (size_t j = 0; j < entry_count; j++) {
                if (strcmp(entries[j].word, token) == 0) {
                    entries[j].count++;
                    found = 1;
                    break;
                }
            }

            if (!found) {
                if (entry_count >= entry_capacity) {
                    size_t new_capacity = entry_capacity == 0 ? 16 : entry_capacity * 2;
                    WordEntry *new_entries = realloc(entries, new_capacity * sizeof(WordEntry));
                    if (new_entries == NULL) {
                        free(str_copy);
                        goto cleanup;
                    }
                    entries = new_entries;
                    entry_capacity = new_capacity;
                }

                char *new_word = strdup(token);
                if (new_word == NULL) {
                    free(str_copy);
                    goto cleanup;
                }

                entries[entry_count].word = new_word;
                entries[entry_count].count = 1;
                entry_count++;
            }

            token = strtok(NULL, " \t\n\r");
        }
        free(str_copy);
    }

    if (entry_count > 0) {
        size_t max_index = 0;
        for (size_t i = 1; i < entry_count; i++) {
            if (entries[i].count > entries[max_index].count) {
                max_index = i;
            }
        }
        result = strdup(entries[max_index].word);
    }

cleanup:
    for (size_t i = 0; i < entry_count; i++) {
        free(entries[i].word);
    }
    free(entries);

    return result;
}

int main(void) {
    char *list[] = {
        "hello world hello",
        "world of c programming",
        "hello c world"
    };

    size_t count = sizeof(list) / sizeof(list[0]);

    char *most_frequent = get_most_frequent_word(list, count);
    if (most_frequent != NULL) {
        printf("%s\n", most_frequent);
        free(most_frequent);
    }

    return 0;
}