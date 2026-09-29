#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 100
#define MAX_OUTPUT_LEN (MAX_WORDS * MAX_WORD_LEN)

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char *words[MAX_WORDS];
    int count;
} WordList;

void init_word_list(WordList *list) {
    list->count = 0;
    for (int i = 0; i < MAX_WORDS; i++) {
        list->words[i] = NULL;
    }
}

void free_word_list(WordList *list) {
    for (int i = 0; i < list->count; i++) {
        free(list->words[i]);
        list->words[i] = NULL;
    }
    list->count = 0;
}

int contains_word(WordList *list, const char *word) {
    if (word == NULL || list == NULL) return 0;
    for (int i = 0; i < list->count; i++) {
        if (list->words[i] != NULL && strcmp(list->words[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

int add_word(WordList *list, const char *word) {
    if (list == NULL || word == NULL || list->count >= MAX_WORDS) {
        return 0;
    }
    
    size_t len = strnlen(word, MAX_WORD_LEN);
    if (len >= MAX_WORD_LEN) {
        return 0;
    }
    if (len == 0) {
        return 0;
    }
    
    char *new_word = malloc(len + 1);
    if (new_word == NULL) {
        return 0;
    }
    
    if (len + 1 < len) {
        free(new_word);
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(new_word, word, len);
    new_word[len] = '\0';
    
    if (list->count < MAX_WORDS) {
        list->words[list->count] = new_word;
        list->count++;
        return 1;
    }
    
    free(new_word);
    return 0;
}

void remove_duplicate_words(const char *input, char *output, size_t output_size) {
    WordList seen;
    init_word_list(&seen);
    
    if (input == NULL || output == NULL || output_size == 0) {
        return;
    }
    output[0] = '\0';
    
    size_t input_len = strnlen(input, MAX_OUTPUT_LEN);
    if (input_len >= MAX_OUTPUT_LEN) {
        free_word_list(&seen);
        return;
    }
    if (input_len == 0) {
        free_word_list(&seen);
        return;
    }
    
    /* Possible weaknesses found:
     *  copy_size is assigned 'input_len+1' here.
     */
    size_t copy_size = input_len + 1;
    char *copy = malloc(copy_size);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (copy == NULL) {
        free_word_list(&seen);
        return;
    }
    
    /* Possible weaknesses found:
     *  Condition 'copy_size>=input_len+1' is always true [knownConditionTrueFalse]
     *  Condition 'copy_size>=input_len+1' is always true
     */
    if (copy_size >= input_len + 1) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, input, input_len);
        copy[input_len] = '\0';
    }
    
    char *result = malloc(MAX_OUTPUT_LEN + 1);
    if (result == NULL) {
        free(copy);
        free_word_list(&seen);
        return;
    }
    result[0] = '\0';
    
    char *saveptr;
    char *token = strtok_r(copy, " \t\n\r", &saveptr);
    int first = 1;
    size_t result_len = 0;
    
    while (token != NULL) {
        if (!contains_word(&seen, token)) {
            if (!add_word(&seen, token)) {
                token = strtok_r(NULL, " \t\n\r", &saveptr);
                continue;
            }
            size_t token_len = strnlen(token, MAX_WORD_LEN);
            if (token_len >= MAX_WORD_LEN) {
                token = strtok_r(NULL, " \t\n\r", &saveptr);
                continue;
            }
            size_t space_needed = first ? 0 : 1;
            
            if (result_len + space_needed + token_len < MAX_OUTPUT_LEN) {
                if (!first && result_len < MAX_OUTPUT_LEN) {
                    result[result_len] = ' ';
                    result_len++;
                }
                if (result_len + token_len < MAX_OUTPUT_LEN) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(result + result_len, token, token_len);
                    result_len += token_len;
                    if (result_len < MAX_OUTPUT_LEN) {
                        result[result_len] = '\0';
                    }
                }
                first = 0;
            } else {
                break;
            }
        }
        token = strtok_r(NULL, " \t\n\r", &saveptr);
    }
    
    size_t copy_len = result_len;
    if (copy_len >= output_size) {
        copy_len = output_size > 0 ? output_size - 1 : 0;
    }
    
    if (copy_len > 0 && output_size > 0 && copy_len < output_size) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(output, result, copy_len);
        output[copy_len] = '\0';
    } else if (output_size > 0) {
        output[0] = '\0';
    }
    
    free_word_list(&seen);
    free(result);
    free(copy);
}

int main(void) {
    char *input = NULL;
    char *output = NULL;
    size_t output_size = MAX_OUTPUT_LEN;

    input = malloc(MAX_OUTPUT_LEN + 1);
    if (input == NULL) {
        fprintf(stderr, "Error allocating memory.\n");
        return 1;
    }

    output = malloc(output_size + 1);
    if (output == NULL) {
        fprintf(stderr, "Error allocating memory.\n");
        free(input);
        return 1;
    }

    printf("Enter a string: ");
    if (fgets(input, MAX_OUTPUT_LEN, stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        free(input);
        free(output);
        return 1;
    }

    size_t len = strnlen(input, MAX_OUTPUT_LEN);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    remove_duplicate_words(input, output, output_size);

    printf("Original: %s\n", input);
    printf("After removing duplicates: %s\n", output);

    free(input);
    free(output);
    return 0;
}