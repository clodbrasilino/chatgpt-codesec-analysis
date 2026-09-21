#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static size_t safe_strlen(const char* str) {
    if (str == NULL) {
        return 0;
    }
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

char** shortlist_words(char** words, int num_words, int n, int* return_count) {
    if (words == NULL || return_count == NULL || num_words < 0 || n < 0) {
        return NULL;
    }

    char** result = NULL;
    int count = 0;

    for (int i = 0; i < num_words; i++) {
        if (words[i] != NULL) {
            if (safe_strlen(words[i]) > (size_t)n) {
                count++;
            }
        }
    }

    if (count > 0) {
        result = (char**)malloc(count * sizeof(char*));
        if (result == NULL) {
            return NULL;
        }

        int index = 0;
        for (int i = 0; i < num_words; i++) {
            if (words[i] != NULL) {
                size_t full_len = safe_strlen(words[i]);
                if (full_len > (size_t)n) {
                    result[index] = (char*)malloc(full_len + 1);
                    if (result[index] == NULL) {
                        for (int j = 0; j < index; j++) {
                            free(result[j]);
                        }
                        free(result);
                        return NULL;
                    }
                    snprintf(result[index], full_len + 1, "%s", words[i]);
                    index++;
                }
            }
        }
    }

    *return_count = count;
    return result;
}

int main(void) {
    char* words[] = {"apple", "cat", "banana", "dog", "elephant", "fox"};
    int num_words = sizeof(words) / sizeof(words[0]);
    int n = 4;
    int return_count = 0;

    char** result = shortlist_words(words, num_words, n, &return_count);

    if (result != NULL) {
        for (int i = 0; i < return_count; i++) {
            printf("%s\n", result[i]);
            free(result[i]);
        }
        free(result);
    }

    return 0;
}