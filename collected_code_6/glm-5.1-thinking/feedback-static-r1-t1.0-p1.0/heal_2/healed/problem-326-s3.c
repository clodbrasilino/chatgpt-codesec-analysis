#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *word;
    int count;
} WordEntry;

static char *string_duplicate(const char *s) {
    size_t max_len = 1024 * 1024;
    const char *end = memchr(s, '\0', max_len);
    if (!end) return NULL;
    size_t len = end - s + 1;
    char *copy = malloc(len);
    if (copy) {
        memcpy(copy, s, len);
    }
    return copy;
}

char *get_most_frequent_word(char **strings, int num_strings) {
    if (!strings || num_strings <= 0) return NULL;

    WordEntry *entries = NULL;
    int entries_count = 0;
    int entries_capacity = 0;
    char *result = NULL;

    for (int i = 0; i < num_strings; i++) {
        if (!strings[i]) continue;

        char *temp = string_duplicate(strings[i]);
        if (!temp) {
            for (int k = 0; k < entries_count; k++) free(entries[k].word);
            free(entries);
            return NULL;
        }

        char *token = strtok(temp, " \t\n\r");
        while (token != NULL) {
            int found = 0;
            for (int j = 0; j < entries_count; j++) {
                if (strcmp(entries[j].word, token) == 0) {
                    entries[j].count++;
                    found = 1;
                    break;
                }
            }

            if (!found) {
                if (entries_count >= entries_capacity) {
                    entries_capacity = entries_capacity == 0 ? 4 : entries_capacity * 2;
                    WordEntry *new_entries = realloc(entries, entries_capacity * sizeof(WordEntry));
                    if (!new_entries) {
                        free(temp);
                        for (int k = 0; k < entries_count; k++) free(entries[k].word);
                        free(entries);
                        return NULL;
                    }
                    entries = new_entries;
                }
                entries[entries_count].word = string_duplicate(token);
                if (!entries[entries_count].word) {
                    free(temp);
                    for (int k = 0; k < entries_count; k++) free(entries[k].word);
                    free(entries);
                    return NULL;
                }
                entries[entries_count].count = 1;
                entries_count++;
            }
            token = strtok(NULL, " \t\n\r");
        }
        free(temp);
    }

    if (entries_count > 0) {
        int max_idx = 0;
        for (int i = 1; i < entries_count; i++) {
            if (entries[i].count > entries[max_idx].count) {
                max_idx = i;
            }
        }
        result = string_duplicate(entries[max_idx].word);
    }

    for (int i = 0; i < entries_count; i++) {
        free(entries[i].word);
    }
    free(entries);

    return result;
}

int main(void) {
    char *strings[] = {
        "hello world hello",
        "world of c programming",
        "hello from the world of c"
    };
    int num_strings = sizeof(strings) / sizeof(strings[0]);

    char *most_frequent = get_most_frequent_word(strings, num_strings);
    if (most_frequent) {
        printf("%s\n", most_frequent);
        free(most_frequent);
    } else {
        printf("No words found or memory allocation failed.\n");
    }

    return 0;
}