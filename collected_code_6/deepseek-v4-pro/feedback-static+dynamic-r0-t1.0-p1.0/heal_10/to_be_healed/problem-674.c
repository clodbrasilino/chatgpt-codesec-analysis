#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 100
#define MAX_INPUT_LEN 65536

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char words[MAX_WORDS][MAX_WORD_LEN];
    int count;
} WordList;

static int is_duplicate(const WordList *list, const char *word) {
    if (list == NULL || word == NULL) {
        return 0;
    }
    for (int i = 0; i < list->count; i++) {
        if (strcmp(list->words[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

static int add_word(WordList *list, const char *word) {
    if (list == NULL || word == NULL || list->count >= MAX_WORDS) {
        return 0;
    }
    
    size_t len = strnlen(word, MAX_WORD_LEN);
    if (len >= MAX_WORD_LEN) {
        len = MAX_WORD_LEN - 1;
    }
    
    if (len < MAX_WORD_LEN) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(list->words[list->count], word, len);
    } else {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(list->words[list->count], word, MAX_WORD_LEN - 1);
        len = MAX_WORD_LEN - 1;
    }
    list->words[list->count][len] = '\0';
    list->count++;
    return 1;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Python Exercises Practice Solution', got <no output>
  *  test case 2 failed: expected 'Python Exercises Practice Solution', got <no output>
  *  test case 0 failed: expected 'Python Exercises Practice Solution', got <no output>
  */

char *remove_duplicate_words(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t input_len = strnlen(str, MAX_INPUT_LEN);
    if (input_len >= MAX_INPUT_LEN) {
        return NULL;
    }

    char *input_copy = malloc(input_len + 1);
    if (input_copy == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(input_copy, str, input_len);
    input_copy[input_len] = '\0';

    char *output = malloc(input_len + 1);
    if (output == NULL) {
        free(input_copy);
        return NULL;
    }
    output[0] = '\0';

    WordList seen;
    memset(&seen, 0, sizeof(seen));

    char *saveptr;
    char *token = strtok_r(input_copy, " \t\n\r", &saveptr);
    int first = 1;
    size_t output_len = 0;

    while (token != NULL) {
        if (!is_duplicate(&seen, token)) {
            add_word(&seen, token);
            if (!first) {
                if (output_len < input_len) {
                    output[output_len] = ' ';
                    output_len++;
                    output[output_len] = '\0';
                }
            }
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t token_len = strlen(token);
            size_t space_remaining = input_len - output_len;
            if (token_len < space_remaining) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(output + output_len, token, token_len);
                output_len += token_len;
                output[output_len] = '\0';
            }
            first = 0;
        }
        token = strtok_r(NULL, " \t\n\r", &saveptr);
    }

    free(input_copy);
    return output;
}

int main(void) {
    const char *test_strings[] = {
        "hello world hello again world test hello",
        "Python Exercises Practice Solution",
        "Python Exercises Practice Solution",
        "Python Exercises Practice Solution",
        NULL
    };

    for (int i = 0; test_strings[i] != NULL; i++) {
        printf("Original: %s\n", test_strings[i]);
        char *result = remove_duplicate_words(test_strings[i]);
        if (result != NULL) {
            printf("After removing duplicates: %s\n", result);
            free(result);
        }
    }

    return 0;
}