#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 100

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char words[MAX_WORDS][MAX_WORD_LEN];
    int count;
} WordCollection;

void init_collection(WordCollection *collection) {
    collection->count = 0;
}

int contains_word(WordCollection *collection, const char *word) {
    for (int i = 0; i < collection->count; i++) {
        if (strcmp(collection->words[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

int add_word(WordCollection *collection, const char *word) {
    if (collection->count >= MAX_WORDS || contains_word(collection, word)) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t word_len = strlen(word);
    size_t copy_len = word_len < MAX_WORD_LEN ? word_len : MAX_WORD_LEN - 1;
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(collection->words[collection->count], word, copy_len);
    collection->words[collection->count][copy_len] = '\0';
    collection->count++;
    return 1;
}

void remove_duplicate_words(char *str, size_t str_size) {
    if (str == NULL || str_size == 0) {
        return;
    }

    WordCollection collection;
    init_collection(&collection);

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(str);
    char *result = (char *)malloc(input_len + 1);
    if (result == NULL) {
        return;
    }
    result[0] = '\0';

    char *token;
    char *rest = str;
    char *delimiters = " \t\n\r\f\v";
    size_t result_len = 0;
    size_t result_capacity = input_len + 1;

    while ((token = strtok_r(rest, delimiters, &rest)) != NULL) {
        if (!contains_word(&collection, token)) {
            add_word(&collection, token);
            
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t token_len = strlen(token);
            size_t needed_space = result_len + token_len + 2;
            
            if (result_len > 0) {
                if (needed_space > result_capacity) {
                    result_capacity *= 2;
                    char *new_result = (char *)realloc(result, result_capacity);
                    if (new_result == NULL) {
                        free(result);
                        return;
                    }
                    result = new_result;
                }
                /* Possible weaknesses found:
                 * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. Risk is low because the source is a constant character. (risk 1, buffer)
                 */
                strncat(result, " ", result_capacity - result_len - 1);
                result_len++;
            }
            
            if (result_len + token_len + 1 > result_capacity) {
                result_capacity = result_len + token_len + 1;
                char *new_result = (char *)realloc(result, result_capacity);
                if (new_result == NULL) {
                    free(result);
                    return;
                }
                result = new_result;
            }
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
             */
            strncat(result, token, result_capacity - result_len - 1);
            result_len += token_len;
        }
    }

    size_t copy_len = result_len < str_size ? result_len : str_size - 1;
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(str, result, copy_len);
    str[copy_len] = '\0';
    free(result);
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[1000];

    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }

    remove_duplicate_words(str, sizeof(str));

    printf("String after removing duplicates: %s\n", str);

    return 0;
}