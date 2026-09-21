#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 100

typedef struct {
    char **words;
    size_t count;
    size_t capacity;
} WordCollection;

void init_collection(WordCollection *wc, size_t capacity) {
    wc->words = malloc(capacity * sizeof(char *));
    if (wc->words == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    wc->count = 0;
    wc->capacity = capacity;
}

void free_collection(WordCollection *wc) {
    size_t i;
    if (wc == NULL || wc->words == NULL) {
        return;
    }
    for (i = 0; i < wc->count; i++) {
        free(wc->words[i]);
    }
    free(wc->words);
    wc->words = NULL;
    wc->count = 0;
    wc->capacity = 0;
}

int word_exists(const WordCollection *wc, const char *word) {
    size_t i;
    if (wc == NULL || word == NULL) {
        return 0;
    }
    for (i = 0; i < wc->count; i++) {
        if (wc->words[i] != NULL && strcmp(wc->words[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

int add_word(WordCollection *wc, const char *word) {
    char *new_word;
    char **temp;
    size_t word_len;
    
    if (wc == NULL || word == NULL) {
        return 0;
    }
    
    if (wc->count >= wc->capacity) {
        size_t new_capacity = wc->capacity * 2;
        temp = realloc(wc->words, new_capacity * sizeof(char *));
        if (temp == NULL) {
            return 0;
        }
        wc->words = temp;
        wc->capacity = new_capacity;
    }
    
    word_len = strnlen(word, MAX_WORD_LEN);
    if (word_len >= MAX_WORD_LEN) {
        return 0;
    }
    
    new_word = malloc(word_len + 1);
    if (new_word == NULL) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(new_word, word, word_len);
    new_word[word_len] = '\0';
    wc->words[wc->count] = new_word;
    wc->count++;
    return 1;
}

void remove_duplicate_words(const char *input, char *output, size_t output_size) {
    WordCollection seen;
    char *buffer;
    size_t buf_idx = 0;
    size_t out_idx = 0;
    size_t i;
    int first_word = 1;
    
    if (input == NULL || output == NULL || output_size == 0) {
        return;
    }
    
    output[0] = '\0';
    
    buffer = malloc(MAX_WORD_LEN);
    if (buffer == NULL) {
        return;
    }
    
    init_collection(&seen, 16);
    
    for (i = 0; input[i] != '\0'; i++) {
        if (isspace((unsigned char)input[i])) {
            if (buf_idx > 0) {
                buffer[buf_idx] = '\0';
                if (!word_exists(&seen, buffer)) {
                    size_t word_len;
                    if (!add_word(&seen, buffer)) {
                        free(buffer);
                        free_collection(&seen);
                        return;
                    }
                    word_len = strnlen(buffer, MAX_WORD_LEN);
                    if (out_idx + word_len + 2 < output_size) {
                        if (!first_word) {
                            output[out_idx++] = ' ';
                        }
                        /* Possible weaknesses found:
                         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                         */
                        strncpy(output + out_idx, buffer, output_size - out_idx - 1);
                        out_idx += word_len;
                        output[out_idx] = '\0';
                        first_word = 0;
                    }
                }
                buf_idx = 0;
            }
        } else {
            if (buf_idx < MAX_WORD_LEN - 1) {
                buffer[buf_idx++] = input[i];
            }
        }
    }
    
    if (buf_idx > 0) {
        buffer[buf_idx] = '\0';
        if (!word_exists(&seen, buffer)) {
            size_t word_len = strnlen(buffer, MAX_WORD_LEN);
            if (out_idx + word_len + 2 < output_size) {
                if (!first_word) {
                    output[out_idx++] = ' ';
                }
                /* Possible weaknesses found:
                 * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                 */
                strncpy(output + out_idx, buffer, output_size - out_idx - 1);
                out_idx += word_len;
                output[out_idx] = '\0';
            }
        }
    }
    
    free(buffer);
    free_collection(&seen);
}

int main(void) {
    const char *test_string = "hello world hello this is is a test world";
    char *result;
    size_t result_size = 1024;
    
    result = malloc(result_size);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    remove_duplicate_words(test_string, result, result_size);
    printf("Original: %s\n", test_string);
    printf("Result:   %s\n", result);
    
    free(result);
    return 0;
}