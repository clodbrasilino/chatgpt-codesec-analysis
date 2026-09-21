#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 50
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'ca', got <no output>
  *  test case 0 failed: expected 'ab', got <no output>
  *  test case 1 failed: expected 'None', got <no output>
  */

char* find_first_repeated_word(const char* str) {
    if (str == NULL || *str == '\0') return NULL;

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char words[MAX_WORDS][MAX_WORD_LENGTH] = {0};
    int word_count = 0;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t str_len = strlen(str);
    if (str_len >= (size_t)(MAX_WORDS * MAX_WORD_LENGTH)) return NULL;

    char* temp_str = (char*)malloc(str_len + 1);
    if (temp_str == NULL) return NULL;
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp_str, str, str_len + 1);

    const char* token = strtok(temp_str, " ");
    while (token != NULL && word_count < MAX_WORDS) {
        size_t token_len = strnlen(token, MAX_WORD_LENGTH);
        if (token_len >= MAX_WORD_LENGTH) {
            token = strtok(NULL, " ");
            continue;
        }
        for (int i = 0; i < word_count; ++i) {
            if (strncmp(words[i], token, MAX_WORD_LENGTH) == 0) {
                free(temp_str);
                return (char*)token;
            }
        }
        snprintf(words[word_count], sizeof(words[word_count]), "%s", token);
        word_count++;
        token = strtok(NULL, " ");
    }
    free(temp_str);
    return NULL;
}

int main() {
    const char* input = "This is a test to find the first repeated word in this string";
    char* result = find_first_repeated_word(input);
    if (result) {
        printf("First repeated word: %s\n", result);
    } else {
        printf("No repeated word found.\n");
    }
    return 0;
}