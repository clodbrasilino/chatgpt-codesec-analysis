#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *word;
    int count;
} WordEntry;

char *get_most_frequent_word(char **strings, int num_strings) {
    if (strings == NULL || num_strings <= 0) {
        return NULL;
    }

    int capacity = 256;
    int size = 0;
    WordEntry *entries = malloc(capacity * sizeof(WordEntry));
    if (entries == NULL) {
        return NULL;
    }

    for (int i = 0; i < num_strings; i++) {
        if (strings[i] == NULL) {
            continue;
        }

        size_t len = strnlen(strings[i], 1024 * 1024);
        char *buffer = malloc(len + 1);
        if (buffer == NULL) {
            for (int k = 0; k < size; k++) free(entries[k].word);
            free(entries);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(buffer, strings[i], len);
        buffer[len] = '\0';

        char *token = strtok(buffer, " \t\n\r.,;:!?\"'()[]{}");
        while (token != NULL) {
            int found = 0;
            for (int j = 0; j < size; j++) {
                if (strcmp(entries[j].word, token) == 0) {
                    entries[j].count++;
                    found = 1;
                    break;
                }
            }

            if (!found) {
                if (size >= capacity) {
                    capacity *= 2;
                    WordEntry *temp = realloc(entries, capacity * sizeof(WordEntry));
                    if (temp == NULL) {
                        for (int k = 0; k < size; k++) free(entries[k].word);
                        free(entries);
                        free(buffer);
                        return NULL;
                    }
                    entries = temp;
                }
                
                /* Possible weaknesses found:
                 * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                 */
                size_t token_len = strlen(token);
                entries[size].word = malloc(token_len + 1);
                if (entries[size].word == NULL) {
                    for (int k = 0; k < size; k++) free(entries[k].word);
                    free(entries);
                    free(buffer);
                    return NULL;
                }
                /* Possible weaknesses found:
                 * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                 */
                strncpy(entries[size].word, token, token_len);
                entries[size].word[token_len] = '\0';
                entries[size].count = 1;
                size++;
            }

            token = strtok(NULL, " \t\n\r.,;:!?\"'()[]{}");
        }
        free(buffer);
    }

    if (size == 0) {
        free(entries);
        return NULL;
    }

    int max_index = 0;
    for (int i = 1; i < size; i++) {
        if (entries[i].count > entries[max_index].count) {
            max_index = i;
        }
    }

    char *result = entries[max_index].word;

    for (int i = 0; i < size; i++) {
        if (i != max_index) {
            free(entries[i].word);
        }
    }
    free(entries);

    return result;
}

int main() {
    char *str_list[] = {
        "hello world, this is a test.",
        "hello again, this is another test.",
        "hello world, hello!"
    };

    int num_strings = sizeof(str_list) / sizeof(str_list[0]);

    char *most_frequent = get_most_frequent_word(str_list, num_strings);
    
    if (most_frequent != NULL) {
        printf("%s\n", most_frequent);
        free(most_frequent);
    } else {
        printf("No words found.\n");
    }

    return 0;
}