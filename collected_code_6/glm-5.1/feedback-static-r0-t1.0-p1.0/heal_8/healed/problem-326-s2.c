#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *word;
    int count;
} WordEntry;

char *duplicate_string(const char *str, size_t max_len) {
    if (!str) return NULL;
    size_t len = strnlen(str, max_len);
    if (len == max_len) return NULL;
    char *dup = malloc(len + 1);
    if (!dup) return NULL;
    memcpy(dup, str, len + 1);
    dup[len] = '\0';
    return dup;
}

void cleanup(WordEntry *entries, int size, char *buffer, char *most_frequent_word) {
    if (buffer) free(buffer);
    for (int e = 0; e < size; e++) free(entries[e].word);
    free(entries);
    if (most_frequent_word) free(most_frequent_word);
}

char *get_word_with_most_occurrences(char **strings, int num_strings) {
    if (!strings || num_strings <= 0) return NULL;

    int capacity = 128;
    int size = 0;
    WordEntry *entries = malloc(capacity * sizeof(WordEntry));
    if (!entries) return NULL;

    char *most_frequent_word = NULL;
    int max_count = 0;

    for (int i = 0; i < num_strings; i++) {
        if (!strings[i]) continue;

        size_t buf_size = strnlen(strings[i], 1024 * 1024) + 1;
        char *buffer = malloc(buf_size);
        if (!buffer) {
            cleanup(entries, size, NULL, most_frequent_word);
            return NULL;
        }
        
        snprintf(buffer, buf_size, "%s", strings[i]);

        char *saveptr;
        char *token = strtok_r(buffer, " \t\n\r.,;:!?\"'()[]{}", &saveptr);
        while (token != NULL) {
            size_t cbuf_size = strnlen(token, 1024 * 1024) + 1;
            char *clean_token = malloc(cbuf_size);
            if (!clean_token) {
                cleanup(entries, size, buffer, most_frequent_word);
                return NULL;
            }
            
            int j = 0;
            for (int k = 0; token[k] != '\0'; k++) {
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
                        most_frequent_word = duplicate_string(entries[found_index].word, strnlen(entries[found_index].word, 1024 * 1024) + 1);
                    }
                } else {
                    if (size >= capacity) {
                        capacity *= 2;
                        WordEntry *new_entries = realloc(entries, capacity * sizeof(WordEntry));
                        if (!new_entries) {
                            free(clean_token);
                            cleanup(entries, size, buffer, most_frequent_word);
                            return NULL;
                        }
                        entries = new_entries;
                    }
                    entries[size].word = duplicate_string(clean_token, strnlen(clean_token, 1024 * 1024) + 1);
                    if (!entries[size].word) {
                        free(clean_token);
                        cleanup(entries, size, buffer, most_frequent_word);
                        return NULL;
                    }
                    entries[size].count = 1;
                    if (entries[size].count > max_count) {
                        max_count = entries[size].count;
                        free(most_frequent_word);
                        most_frequent_word = duplicate_string(entries[size].word, strnlen(entries[size].word, 1024 * 1024) + 1);
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