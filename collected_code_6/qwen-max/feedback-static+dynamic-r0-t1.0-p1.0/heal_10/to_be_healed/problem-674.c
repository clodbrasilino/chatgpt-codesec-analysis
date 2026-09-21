#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1024
#define MAX_WORD_LENGTH 64
#define RESULT_BUFFER_SIZE (MAX_WORDS * (MAX_WORD_LENGTH + 1) + 1)

int is_word_in_array(const char *word, const char **words, int num_words) {
    for (int i = 0; i < num_words; ++i) {
        if (strcmp(word, words[i]) == 0) {
            return 1;
        }
    }
    return 0;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'Python Exercises Practice Solution', got <no output>
  *  test case 0 failed: expected 'Python Exercises Practice Solution', got <no output>
  *  test case 1 failed: expected 'Python Exercises Practice Solution', got <no output>
  */

char *remove_duplicate_words(const char *input) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     *  Variable 'input_len' is assigned a value that is never used. [unreadVariable]
     *  Value stored to 'input_len' during its initialization is never read [deadcode.DeadStores]
     */
    size_t input_len = strlen(input);
    char *result = (char *)malloc(RESULT_BUFFER_SIZE);
    if (result == NULL) {
        return NULL;
    }
    result[0] = '\0';

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char *words[MAX_WORDS];
    for (int i = 0; i < MAX_WORDS; ++i) {
        words[i] = (char *)malloc(MAX_WORD_LENGTH + 1);
        if (words[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                free(words[j]);
            }
            free(result);
            return NULL;
        }
        words[i][0] = '\0';
    }

    int num_words = 0;

    const char *p = input;

    while (*p) {
        while (*p && !isalnum((unsigned char)*p)) p++;
        const char *word_start = p;
        while (*p && isalnum((unsigned char)*p)) p++;

        if (word_start != p) {
            size_t word_len = p - word_start;
            if (word_len <= MAX_WORD_LENGTH && !is_word_in_array(word_start, (const char *const *)words, num_words)) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(words[num_words], word_start, word_len);
                words[num_words][word_len] = '\0';

                /* Possible weaknesses found:
                 * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
                 */
                strncat(result, words[num_words], MAX_WORD_LENGTH + 1);
                /* Possible weaknesses found:
                 * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. Risk is low because the source is a constant character. (risk 1, buffer)
                 */
                strncat(result, " ", 2);

                num_words++;
            }
        }

        if (num_words >= MAX_WORDS) {
            for (int i = 0; i < MAX_WORDS; ++i) {
                free(words[i]);
            }
            free(result);
            return NULL;
        }
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t result_len = strlen(result);
    if (result_len > 0 && result[result_len - 1] == ' ') {
        result[--result_len] = '\0';
    }

    for (int i = 0; i < MAX_WORDS; ++i) {
        free(words[i]);
    }

    return result;
}

int main() {
    const char *input = "Python Python Exercises Practice Solution";
    char *output = remove_duplicate_words(input);

    if (output == NULL) {
        fprintf(stderr, "Error: Memory allocation failed or too many unique words.\n");
        return 1;
    }

    printf("Original: %s\n", input);
    printf("Processed: %s\n", output);

    free(output);
    return 0;
}