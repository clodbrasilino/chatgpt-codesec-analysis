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
    char *dst = malloc(len);
    if (dst) {
        memcpy(dst, src, len);
    }
    return dst;
}

char *get_most_frequent_word(char **strings, int num_strings) {
    if (strings == NULL || num_strings <= 0) {
        return NULL;
    }

    int capacity = 16;
    int size = 0;
    WordEntry *entries = malloc(capacity * sizeof(WordEntry));
    if (entries == NULL) {
        return NULL;
    }

    for (int i = 0; i < num_strings; i++) {
        if (strings[i] == NULL) {
            continue;
        }

        char buffer[256];
        int buf_idx = 0;

        for (int j = 0; strings[i][j] != '\0'; j++) {
            if (isalpha((unsigned char)strings[i][j])) {
                buffer[buf_idx++] = tolower((unsigned char)strings[i][j]);
                if (buf_idx >= (int)sizeof(buffer) - 1) {
                    break;
                }
            } else if (buf_idx > 0) {
                buffer[buf_idx] = '\0';
                buf_idx = 0;

                int found = 0;
                for (int k = 0; k < size; k++) {
                    if (strcmp(entries[k].word, buffer) == 0) {
                        entries[k].count++;
                        found = 1;
                        break;
                    }
                }

                if (!found) {
                    if (size >= capacity) {
                        capacity *= 2;
                        WordEntry *temp = realloc(entries, capacity * sizeof(WordEntry));
                        if (temp == NULL) {
                            for (int l = 0; l < size; l++) free(entries[l].word);
                            free(entries);
                            return NULL;
                        }
                        entries = temp;
                    }
                    entries[size].word = strdup_custom(buffer);
                    if (entries[size].word == NULL) {
                        for (int l = 0; l < size; l++) free(entries[l].word);
                        free(entries);
                        return NULL;
                    }
                    entries[size].count = 1;
                    size++;
                }
            }
        }

        if (buf_idx > 0) {
            buffer[buf_idx] = '\0';

            int found = 0;
            for (int k = 0; k < size; k++) {
                if (strcmp(entries[k].word, buffer) == 0) {
                    entries[k].count++;
                    found = 1;
                    break;
                }
            }

            if (!found) {
                if (size >= capacity) {
                    capacity *= 2;
                    WordEntry *temp = realloc(entries, capacity * sizeof(WordEntry));
                    if (temp == NULL) {
                        for (int l = 0; l < size; l++) free(entries[l].word);
                        free(entries);
                        return NULL;
                    }
                    entries = temp;
                }
                entries[size].word = strdup_custom(buffer);
                if (entries[size].word == NULL) {
                    for (int l = 0; l < size; l++) free(entries[l].word);
                    free(entries);
                    return NULL;
                }
                entries[size].count = 1;
                size++;
            }
        }
    }

    if (size == 0) {
        free(entries);
        return NULL;
    }

    int max_idx = 0;
    for (int i = 1; i < size; i++) {
        if (entries[i].count > entries[max_idx].count) {
            max_idx = i;
        }
    }

    char *result = entries[max_idx].word;

    for (int i = 0; i < size; i++) {
        if (i != max_idx) {
            free(entries[i].word);
        }
    }
    free(entries);

    return result;
}

int main(void) {
    char *strings[] = {
        "Hello world! This is a test.",
        "Hello again, this test is only a test.",
        "A big hello to the world."
    };

    int num_strings = sizeof(strings) / sizeof(strings[0]);

    char *most_frequent = get_most_frequent_word(strings, num_strings);

    if (most_frequent != NULL) {
        printf("Most frequent word: %s\n", most_frequent);
        free(most_frequent);
    } else {
        printf("No words found.\n");
    }

    return 0;
}