#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 100
#define MAX_INPUT_LEN 2048

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char words[MAX_WORDS][MAX_WORD_LEN];
    int count;
} WordList;

void init_word_list(WordList *list) {
    if (list == NULL) {
        return;
    }
    list->count = 0;
    memset(list->words, 0, sizeof(list->words));
}

int contains_word(const WordList *list, const char *word) {
    if (list == NULL || word == NULL) {
        return 0;
    }
    for (int i = 0; i < list->count; i++) {
        if (strncmp(list->words[i], word, MAX_WORD_LEN - 1) == 0) {
            return 1;
        }
    }
    return 0;
}

int add_word(WordList *list, const char *word) {
    if (list == NULL || word == NULL) {
        return 0;
    }
    
    if (list->count >= MAX_WORDS) {
        return 0;
    }
    
    size_t len = strnlen(word, MAX_WORD_LEN);
    
    if (len >= MAX_WORD_LEN) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(list->words[list->count], word, MAX_WORD_LEN - 1);
    list->words[list->count][MAX_WORD_LEN - 1] = '\0';
    list->count++;
    return 1;
}

size_t safe_strlen(const char *str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }
    return strnlen(str, max_len);
}

void remove_duplicate_words(const char *input, char *output, size_t output_size) {
    if (input == NULL || output == NULL || output_size == 0) {
        if (output != NULL && output_size > 0) {
            output[0] = '\0';
        }
        return;
    }
    
    WordList seen;
    init_word_list(&seen);
    
    output[0] = '\0';
    
    size_t input_len = strnlen(input, MAX_INPUT_LEN);
    if (input_len >= MAX_INPUT_LEN) {
        return;
    }
    
    char *copy = malloc(input_len + 1);
    if (copy == NULL) {
        return;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, input, input_len);
    copy[input_len] = '\0';
    
    size_t remaining = output_size;
    char *current_pos = output;
    int first = 1;
    
    char *saveptr;
    char *token = strtok_r(copy, " \t\n\r", &saveptr);
    
    while (token != NULL) {
        if (!contains_word(&seen, token)) {
            if (!add_word(&seen, token)) {
                free(copy);
                output[0] = '\0';
                return;
            }
            
            size_t token_len = strnlen(token, MAX_WORD_LEN);
            if (token_len >= MAX_WORD_LEN) {
                free(copy);
                output[0] = '\0';
                return;
            }
            
            size_t needed;
            if (first) {
                needed = token_len + 1;
            } else {
                needed = token_len + 2;
            }
            
            if (needed > remaining) {
                free(copy);
                output[0] = '\0';
                return;
            }
            
            if (!first) {
                if (remaining > 0) {
                    *current_pos = ' ';
                    current_pos++;
                    remaining--;
                }
            }
            
            if (token_len >= remaining) {
                free(copy);
                output[0] = '\0';
                return;
            }
            
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(current_pos, token, token_len);
            current_pos += token_len;
            remaining -= token_len;
            *current_pos = '\0';
            first = 0;
        }
        token = strtok_r(NULL, " \t\n\r", &saveptr);
    }
    
    free(copy);
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT_LEN];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[MAX_INPUT_LEN];
    
    memset(input, 0, sizeof(input));
    memset(output, 0, sizeof(output));
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }
    
    size_t len = strnlen(input, sizeof(input));
    if (len > 0 && len < sizeof(input) && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else if (len > 0) {
        input[sizeof(input) - 1] = '\0';
    }
    
    remove_duplicate_words(input, output, sizeof(output));
    
    printf("Original: %s\n", input);
    printf("After removing duplicates: %s\n", output);
    
    return 0;
}