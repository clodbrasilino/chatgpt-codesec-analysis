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
                } else {
                    goto cleanup;
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
    str[0] = '\0';

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp[1024];
    while (fgets(temp, sizeof(temp), stdin) != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t temp_len = strlen(temp);
        if (len + temp_len + 1 >= size) {
            size_t new_size = (len + temp_len + 1) * 2;
            char* new_str = (char*)realloc(str, new_size);
            if (new_str == NULL) {
                free(str);
                return 1;
            }
            str = new_str;
            size = new_size;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(str + len, temp, temp_len);
        len += temp_len;
        str[len] = '\0';
    }

    char* repeated_word = find_first_repeated_word(str);

    if (repeated_word != NULL) {
        printf("%s\n", repeated_word);
        free(repeated_word);
    }

    free(str);
    return 0;
}