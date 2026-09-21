#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *find_first_max_even_word(const char *str, size_t str_len) {
    if (str == NULL || str_len == 0) {
        return NULL;
    }

    size_t pos = 0;
    size_t max_len = 0;
    char *max_word = NULL;

    while (pos < str_len) {
        while (pos < str_len && !isalpha((unsigned char)str[pos])) {
            pos++;
        }

        if (pos >= str_len) {
            break;
        }

        size_t word_start = pos;
        while (pos < str_len && isalpha((unsigned char)str[pos])) {
            pos++;
        }
        size_t word_len = pos - word_start;

        if (word_len % 2 == 0 && word_len > 0 && word_len > max_len) {
            max_len = word_len;
            /* Possible weaknesses found:
             *  needed is assigned 'word_len+1' here.
             */
            size_t needed = word_len + 1;

            /* Possible weaknesses found:
             *  Condition 'needed<word_len' is always false [knownConditionTrueFalse]
             *  Condition 'needed<word_len' is always false
             */
            if (needed < word_len) {
                free(max_word);
                return NULL;
            }

            char *new_word = realloc(max_word, needed);
            if (new_word == NULL) {
                free(max_word);
                return NULL;
            }
            max_word = new_word;

            if (word_start + word_len <= str_len) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(max_word, str + word_start, word_len);
                max_word[word_len] = '\0';
            }
        }
    }

    return max_word;
}

int main(void) {
    const char test_string[] = "This is a test string with several words of different lengths";
    size_t test_len = sizeof(test_string) - 1;
    char *result = find_first_max_even_word(test_string, test_len);

    if (result != NULL) {
        printf("First max even word: %s\n", result);
        free(result);
    } else {
        printf("No even word found or memory allocation failed.\n");
    }

    return 0;
}