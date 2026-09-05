#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *word;
    int count;
} WordEntry;

char *strdup_custom(const char *src) {
    size_t len = strlen(src) + 1;
    char *dst = (char *)malloc(len);
    if (!dst) return NULL;
    memcpy(dst, src, len);
    return dst;
}

char *get_most_frequent_word(char **strings, int num_strings) {
    if (!strings || num_strings <= 0) return NULL;

    int capacity = 256;
    int size = 0;
    WordEntry *entries = (WordEntry *)malloc(capacity * sizeof(WordEntry));
    if (!entries) return NULL;

    char *most_frequent_word = NULL;
    int max_count = 0;

    for (int i = 0; i < num_strings; i++) {
        if (!strings[i]) continue;

        char buffer[1024];
        strncpy(buffer, strings[i], sizeof(buffer) - 1);
        buffer[sizeof(buffer) - 1] = '\0';

        char *token = strtok(buffer, " \t\n\r.,;:!?\"'()[]{}");
        while (token != NULL) {
            if (size >= capacity) {
                capacity *= 2;
                WordEntry *new_entries = (WordEntry *)realloc(entries, capacity * sizeof(WordEntry));
                if (!new_entries) {
                    for (int j = 0; j < size; j++) free(entries[j].word);
                    free(entries);
                    return NULL;
                }
                entries = new_entries;
            }

            int found = 0;
            for (int j = 0; j < size; j++) {
                if (strcmp(entries[j].word, token) == 0) {
                    entries[j].count++;
                    if (entries[j].count > max_count) {
                        max_count = entries[j].count;
                        most_frequent_word = entries[j].word;
                    }
                    found = 1;
                    break;
                }
            }

            if (!found) {
                entries[size].word = strdup_custom(token);
                if (!entries[size].word) {
                    for (int j = 0; j < size; j++) free(entries[j].word);
                    free(entries);
                    return NULL;
                }
                entries[size].count = 1;
                if (max_count < 1) {
                    max_count = 1;
                    most_frequent_word = entries[size].word;
                }
                size++;
            }

            token = strtok(NULL, " \t\n\r.,;:!?\"'()[]{}");
        }
    }

    char *result = NULL;
    if (most_frequent_word) {
        result = strdup_custom(most_frequent_word);
    }

    for (int i = 0; i < size; i++) {
        free(entries[i].word);
    }
    free(entries);

    return result;
}

int main() {
    char *strings[] = {
        "hello world, this is a test.",
        "hello again, this is another test.",
        "hello world, hello!"
    };
    int num_strings = sizeof(strings) / sizeof(strings[0]);

    char *most_frequent = get_most_frequent_word(strings, num_strings);
    if (most_frequent) {
        printf("%s\n", most_frequent);
        free(most_frequent);
    } else {
        printf("No words found.\n");
    }

    return 0;
}