#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *word;
    int count;
} WordEntry;

char *duplicate_string(const char *str, size_t max_len) {
    size_t len = strnlen(str, max_len);
    if (len == 0) {
        char *dup = malloc(1);
        if (!dup) return NULL;
        dup[0] = '\0';
        return dup;
    }
    if (len + 1 <= len) return NULL;
    char *dup = malloc(len + 1);
    if (!dup) return NULL;
    memcpy(dup, str, len);
    dup[len] = '\0';
    return dup;
}

void cleanup(WordEntry *entries, int size, char *most_frequent_word, char *buffer, char *clean_token) {
    if (clean_token) free(clean_token);
    if (buffer) free(buffer);
    for (int e = 0; e < size; e++) free(entries[e].word);
    free(entries);
    free(most_frequent_word);
}

char *get_word_with_most_occurrences(char **strings, int num_strings) {
    if (!strings || num_strings <= 0) return NULL;

    int capacity = 128;
    int size = 0;
    WordEntry *entries = malloc(((size_t)capacity) * sizeof(WordEntry));
    if (!entries) return NULL;

    char *most_frequent_word = NULL;
    int max_count = 0;

    for (int i = 0; i < num_strings; i++) {
        if (!strings[i]) continue;

        size_t input_len = strnlen(strings[i], 4096);
        if (input_len == 0) continue;

        if (input_len + 1 <= input_len) {
            cleanup(entries, size, most_frequent_word, NULL, NULL);
            return NULL;
        }
        char *buffer = malloc(input_len + 1);
        if (!buffer) {
            cleanup(entries, size, most_frequent_word, NULL, NULL);
            return NULL;
        }
        memcpy(buffer, strings[i], input_len);
        buffer[input_len] = '\0';

        char *saveptr;
        char *token = strtok_r(buffer, " \t\n\r.,;:!?\"'()[]{}", &saveptr);
        while (token != NULL) {
            size_t token_len = strnlen(token, 4096);
            char *clean_token = malloc(token_len + 1);
            if (!clean_token) {
                cleanup(entries, size, most_frequent_word, buffer, NULL);
                return NULL;
            }
            int j = 0;
            for (int k = 0; k < token_len && token[k] != '\0'; k++) {
                if (isalpha((unsigned char)token[k])) {
                    clean_token[j++] = tolower((unsigned char)token[k]);
                }
            }
            clean_token[j] = '\0';

            if (j > 0) {
                int found_index = -1;
                for (int e = 0; e < size; e++) {
                    if (strcmp(entries[e].word, clean_token) == 0) {
                        found_index = e;
                        break;
                    }
                }

                if (found_index != -1) {
                    entries[found_index].count++;
                    if (entries[found_index].count > max_count) {
                        max_count = entries[found_index].count;
                        free(most_frequent_word);
                        most_frequent_word = duplicate_string(entries[found_index].word, token_len);
                    }
                } else {
                    if (size >= capacity) {
                        capacity *= 2;
                        WordEntry *new_entries = realloc(entries, ((size_t)capacity) * sizeof(WordEntry));
                        if (!new_entries) {
                            cleanup(entries, size, most_frequent_word, buffer, clean_token);
                            return NULL;
                        }
                        entries = new_entries;
                    }
                    entries[size].word = duplicate_string(clean_token, token_len);
                    if (!entries[size].word) {
                        cleanup(entries, size, most_frequent_word, buffer, clean_token);
                        return NULL;
                    }
                    entries[size].count = 1;
                    if (entries[size].count > max_count) {
                        max_count = entries[size].count;
                        free(most_frequent_word);
                        most_frequent_word = duplicate_string(entries[size].word, token_len);
                    }
                    size++;
                }
            }
            free(clean_token);
            token = strtok_r(NULL, " \t\n\r.,;:!?\"'()[]{}", &saveptr);
        }
        free(buffer);
    }

    for (int e = 0; e < size; e++) {
        free(entries[e].word);
    }
    free(entries);

    return most_frequent_word;
}

int main() {
    char *strings[] = {
        "Hello world! Hello everyone.",
        "The world is a beautiful place.",
        "Hello again, world.",
        NULL
    };
    
    int num_strings = 3;
    
    char *result = get_word_with_most_occurrences(strings, num_strings);
    
    if (result) {
        printf("%s\n", result);
        free(result);
    } else {
        printf("No words found.\n");
    }
    
    return 0;
}