#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* find_first_repeated_word(const char* str) {
    if (str == NULL) {
        return strdup("None");
    }

    int max_words = 1000;
    char** words = (char**)malloc(max_words * sizeof(char*));
    if (words == NULL) {
        return strdup("None");
    }

    int word_count = 0;
    const char* p = str;
    
    int max_word_len = 1024;
    char* buffer = (char*)malloc(max_word_len);
    if (buffer == NULL) {
        free(words);
        return strdup("None");
    }
    
    int buf_idx = 0;
    char* result = NULL;

    while (*p != '\0') {
        if (isalpha((unsigned char)*p)) {
            if (buf_idx < max_word_len - 1) {
                buffer[buf_idx++] = tolower((unsigned char)*p);
            } else {
                max_word_len *= 2;
                char* new_buffer = (char*)realloc(buffer, max_word_len);
                if (new_buffer) {
                    buffer = new_buffer;
                    buffer[buf_idx++] = tolower((unsigned char)*p);
                }
            }
        } else if (buf_idx > 0) {
            buffer[buf_idx] = '\0';
            
            for (int i = 0; i < word_count; i++) {
                if (strcmp(words[i], buffer) == 0) {
                    result = strdup(buffer);
                    goto cleanup;
                }
            }

            if (word_count >= max_words) {
                max_words *= 2;
                char** new_words = (char**)realloc(words, max_words * sizeof(char*));
                if (new_words) {
                    words = new_words;
                } else {
                    goto cleanup;
                }
            }

            words[word_count] = strdup(buffer);
            if (words[word_count] == NULL) {
                goto cleanup;
            }
            word_count++;
            buf_idx = 0;
        }
        p++;
    }

    if (buf_idx > 0) {
        buffer[buf_idx] = '\0';
        for (int i = 0; i < word_count; i++) {
            if (strcmp(words[i], buffer) == 0) {
                result = strdup(buffer);
                goto cleanup;
            }
        }
    }

cleanup:
    free(buffer);
    for (int i = 0; i < word_count; i++) {
        free(words[i]);
    }
    free(words);

    if (result == NULL) {
        return strdup("None");
    }

    return result;
}

int main(void) {
    size_t size = 1024;
    size_t len = 0;
    char* str = (char*)malloc(size);
    if (str == NULL) {
        return 1;
    }

    int c;
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != EOF) {
        if (len + 1 >= size) {
            size *= 2;
            char* new_str = (char*)realloc(str, size);
            if (new_str == NULL) {
                free(str);
                return 1;
            }
            str = new_str;
        }
        str[len++] = (char)c;
    }
    str[len] = '\0';

    char* repeated_word = find_first_repeated_word(str);

    if (repeated_word != NULL) {
        printf("%s\n", repeated_word);
        free(repeated_word);
    }

    free(str);
    return 0;
}