#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'None', got (null)
  */

char *find_first_repeated_word(const char *str) {
    if (!str) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len == 0) {
        return NULL;
    }

    char **seen_words = malloc(sizeof(char *) * (len + 1));
    if (!seen_words) {
        return NULL;
    }

    size_t seen_count = 0;
    char *result = NULL;
    const char *ptr = str;

    while (*ptr) {
        while (*ptr && isspace((unsigned char)*ptr)) {
            ptr++;
        }
        if (!*ptr) {
            break;
        }

        const char *start = ptr;
        while (*ptr && !isspace((unsigned char)*ptr)) {
            ptr++;
        }
        size_t word_len = (size_t)(ptr - start);

        char *current_word = malloc(word_len + 1);
        if (!current_word) {
            for (size_t i = 0; i < seen_count; i++) {
                free(seen_words[i]);
            }
            free(seen_words);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(current_word, start, word_len);
        current_word[word_len] = '\0';

        int found = 0;
        for (size_t i = 0; i < seen_count; i++) {
            if (strcmp(seen_words[i], current_word) == 0) {
                found = 1;
                break;
            }
        }

        if (found) {
            result = current_word;
            break;
        } else {
            seen_words[seen_count++] = current_word;
        }
    }

    for (size_t i = 0; i < seen_count; i++) {
        free(seen_words[i]);
    }
    free(seen_words);

    return result;
}

int main(void) {
    const char *test_str = "this is a test and this is only a test";
    char *repeated = find_first_repeated_word(test_str);

    if (repeated) {
        printf("%s\n", repeated);
        free(repeated);
    }

    return 0;
}