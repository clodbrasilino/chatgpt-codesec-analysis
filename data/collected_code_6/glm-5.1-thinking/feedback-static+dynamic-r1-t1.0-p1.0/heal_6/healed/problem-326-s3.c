#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STR_LEN 4096

typedef struct {
    char *word;
    int count;
} WordEntry;

static char *string_duplicate(const char *s) {
    if (!s) {
        return NULL;
    }
    size_t len = strnlen(s, MAX_STR_LEN);
    if (len == MAX_STR_LEN) {
        return NULL;
    }
    char *copy = malloc(len + 1);
    if (copy) {
        snprintf(copy, len + 1, "%s", s);
    }
    return copy;
}

char *get_most_frequent_word(char **strings, int num_strings) {
    WordEntry *entries = NULL;
    int entries_count = 0;
    int entries_capacity = 0;
    char *result = NULL;
    char *temp = NULL;
    int i, j;

    for (i = 0; i < num_strings; i++) {
        temp = string_duplicate(strings[i]);
        if (!temp) {
            goto cleanup;
        }

        char *token = strtok(temp, " \t\n\r");
        while (token != NULL) {
            int found = 0;
            for (j = 0; j < entries_count; j++) {
                if (strcmp(entries[j].word, token) == 0) {
                    entries[j].count++;
                    found = 1;
                    break;
                }
            }

            if (!found) {
                if (entries_count >= entries_capacity) {
                    int new_capacity = entries_capacity == 0 ? 4 : entries_capacity * 2;
                    if (new_capacity < entries_capacity || (size_t)new_capacity > SIZE_MAX / sizeof(WordEntry)) {
                        goto cleanup;
                    }
                    entries_capacity = new_capacity;
                    WordEntry *new_entries = realloc(entries, entries_capacity * sizeof(WordEntry));
                    if (!new_entries) {
                        goto cleanup;
                    }
                    entries = new_entries;
                }
                entries[entries_count].word = string_duplicate(token);
                if (!entries[entries_count].word) {
                    goto cleanup;
                }
                entries[entries_count].count = 1;
                entries_count++;
            }
            token = strtok(NULL, " \t\n\r");
        }
        free(temp);
        temp = NULL;
    }

    if (entries_count > 0) {
        int max_idx = 0;
        for (i = 1; i < entries_count; i++) {
            if (entries[i].count > entries[max_idx].count) {
                max_idx = i;
            }
        }
        result = string_duplicate(entries[max_idx].word);
    }

cleanup:
    free(temp);
    for (i = 0; i < entries_count; i++) {
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