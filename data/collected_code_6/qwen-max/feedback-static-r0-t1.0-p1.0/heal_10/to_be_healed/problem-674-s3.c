#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 50

char** split_string(const char* str, int* word_count) {
    char** words = (char**)malloc(MAX_WORDS * sizeof(char*));
    if (!words) return NULL;

    *word_count = 0;
    size_t len = strnlen(str, MAX_WORD_LENGTH * MAX_WORDS);
    char* temp_str = (char*)malloc((len + 1) * sizeof(char));
    if (!temp_str) {
        free(words);
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp_str, str, len + 1);

    char* token;
    for (token = strtok(temp_str, " "); token && *word_count < MAX_WORDS; token = strtok(NULL, " ")) {
        size_t token_len = strnlen(token, MAX_WORD_LENGTH + 1);
        if (token_len > MAX_WORD_LENGTH || token_len == 0) continue;
        words[*word_count] = (char*)malloc((token_len + 1) * sizeof(char));
        if (!words[*word_count]) {
            while (*word_count > 0) free(words[--*word_count]);
            free(words);
            free(temp_str);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(words[*word_count], token, token_len);
        words[*word_count][token_len] = '\0';
        (*word_count)++;
    }

    free(temp_str);
    return words;
}

void free_words(char** words, int word_count) {
    for (int i = 0; i < word_count; i++) {
        free(words[i]);
    }
    free(words);
}

char* remove_duplicates(const char* str) {
    int word_count = 0;
    char** words = split_string(str, &word_count);
    if (!words) return NULL;

    int unique_count = 0;
    for (int i = 0; i < word_count; i++) {
        int is_duplicate = 0;
        for (int j = 0; j < unique_count; j++) {
            if (strcmp(words[i], words[j]) == 0) {
                is_duplicate = 1;
                break;
            }
        }
        if (!is_duplicate) {
            words[unique_count++] = words[i];
        } else {
            free(words[i]);
        }
    }

    /* Possible weaknesses found:
     *  Assignment 'result_len=0', assigned value is 0
     */
    int result_len = 0;
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    for (int i = 0; i < unique_count; i++) {
        result_len += strnlen(words[i], MAX_WORD_LENGTH + 1) + 2;
    }
    /* Possible weaknesses found:
     *  Compound assignment '-=', assigned value is -1
     */
    result_len -= 1;
    /* Possible weaknesses found:
     *  Negative value is converted to an unsigned value
     *  Expression 'result_len' can have a negative value. That is converted to an unsigned value and used in an unsigned calculation. [signConversion]
     */
    char* result = (char*)malloc(result_len * sizeof(char));
    if (!result) {
        free_words(words, word_count);
        return NULL;
    }
    result[0] = '\0';

    for (int i = 0; i < unique_count; i++) {
        size_t len = strnlen(words[i], MAX_WORD_LENGTH + 1);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (len + strlen(result) + 1 > result_len) {
            free(result);
            free_words(words, word_count);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
         */
        strncat(result, words[i], len + 1);
        if (i < unique_count - 1) {
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. Risk is low because the source is a constant character. (risk 1, buffer)
             */
            strncat(result, " ", 2);
        }
    }

    free_words(words, word_count);
    return result;
}

int main() {
    const char* input = "this this is a test test string string";
    char* result = remove_duplicates(input);
    if (result) {
        printf("%s\n", result);
        free(result);
    } else {
        printf("Error: Not enough memory\n");
    }
    return 0;
}