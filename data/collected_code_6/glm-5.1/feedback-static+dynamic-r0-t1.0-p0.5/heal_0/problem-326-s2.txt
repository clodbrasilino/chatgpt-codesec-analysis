#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *word;
    int count;
} WordEntry;

char *strdup_new(const char *s) {
    size_t len = strlen(s) + 1;
    char *d = malloc(len);
    if (d) {
        memcpy(d, s, len);
    }
    return d;
}

char *get_most_frequent_word(char **strings, int num_strings) {
    WordEntry *entries = NULL;
    int capacity = 0;
    int size = 0;
    char *result = NULL;
    int max_count = 0;

    for (int i = 0; i < num_strings; i++) {
        char *str = strings[i];
        if (str == NULL) {
            continue;
        }

        char *temp = strdup_new(str);
        if (temp == NULL) {
            for (int j = 0; j < size; j++) free(entries[j].word);
            free(entries);
            return NULL;
        }

        char *token = strtok(temp, " \t\n\r.,;:!?\"'()[]{}");
        while (token != NULL) {
            int found = -1;
            for (int j = 0; j < size; j++) {
                if (strcmp(entries[j].word, token) == 0) {
                    found = j;
                    break;
                }
            }

            if (found != -1) {
                entries[found].count++;
            } else {
                if (size >= capacity) {
                    int new_capacity = capacity == 0 ? 16 : capacity * 2;
                    WordEntry *new_entries = realloc(entries, new_capacity * sizeof(WordEntry));
                    if (new_entries == NULL) {
                        free(temp);
                        for (int j = 0; j < size; j++) free(entries[j].word);
                        free(entries);
                        return NULL;
                    }
                    entries = new_entries;
                    capacity = new_capacity;
                }
                entries[size].word = strdup_new(token);
                if (entries[size].word == NULL) {
                    free(temp);
                    for (int j = 0; j < size; j++) free(entries[j].word);
                    free(entries);
                    return NULL;
                }
                entries[size].count = 1;
                size++;
            }

            token = strtok(NULL, " \t\n\r.,;:!?\"'()[]{}");
        }
        free(temp);
    }

    for (int i = 0; i < size; i++) {
        if (entries[i].count > max_count) {
            max_count = entries[i].count;
            result = entries[i].word;
        }
    }

    char *final_result = NULL;
    if (result != NULL) {
        final_result = strdup_new(result);
    }

    for (int i = 0; i < size; i++) {
        free(entries[i].word);
    }
    free(entries);

    return final_result;
}

int main(void) {
    char *strings[] = {
        "hello world, this is a test.",
        "hello again, this is another test.",
        "hello world, hello!"
    };
    int num_strings = sizeof(strings) / sizeof(strings[0]);

    char *most_frequent = get_most_frequent_word(strings, num_strings);
    if (most_frequent != NULL) {
        printf("%s\n", most_frequent);
        free(most_frequent);
    } else {
        printf("No words found or memory allocation failed.\n");
    }

    return 0;
}