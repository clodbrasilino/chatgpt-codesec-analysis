#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *word;
    int count;
} WordEntry;

char *strdup_custom(const char *src) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(src) + 1;
    char *dst = (char *)malloc(len);
    if (!dst) return NULL;
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
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

        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char buffer[1024];
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
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