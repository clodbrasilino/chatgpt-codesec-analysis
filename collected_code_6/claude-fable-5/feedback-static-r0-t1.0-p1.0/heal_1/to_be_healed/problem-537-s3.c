#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1024
#define MAX_WORD_LEN 256

static int extract_words(const char *str, char words[][MAX_WORD_LEN], int max_words)
{
    int count = 0;
    size_t i = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);

    while (i < len && count < max_words) {
        while (i < len && !isalnum((unsigned char)str[i])) {
            i++;
        }
        if (i >= len) {
            break;
        }
        size_t w = 0;
        while (i < len && isalnum((unsigned char)str[i]) && w < MAX_WORD_LEN - 1) {
            words[count][w] = (char)tolower((unsigned char)str[i]);
            w++;
            i++;
        }
        words[count][w] = '\0';
        while (i < len && isalnum((unsigned char)str[i])) {
            i++;
        }
        count++;
    }
    return count;
}

const char *find_first_repeated_word(const char *str, char *result, size_t result_size)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    static char words[MAX_WORDS][MAX_WORD_LEN];
    int count;
    int i;
    int j;

    if (str == NULL || result == NULL || result_size == 0) {
        return NULL;
    }

    count = extract_words(str, words, MAX_WORDS);

    for (i = 1; i < count; i++) {
        for (j = 0; j < i; j++) {
            if (strcmp(words[i], words[j]) == 0) {
                /* Possible weaknesses found:
                 * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                 */
                if (strlen(words[i]) >= result_size) {
                    return NULL;
                }
                /* Possible weaknesses found:
                 * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                 */
                strncpy(result, words[i], result_size - 1);
                result[result_size - 1] = '\0';
                return result;
            }
        }
    }
    return NULL;
}

int main(void)
{
    const char *test1 = "he had had quite enough of this nonsense";
    const char *test2 = "one two three four";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[MAX_WORD_LEN];

    if (find_first_repeated_word(test1, result, sizeof(result)) != NULL) {
        if (printf("First repeated word: %s\n", result) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("No repeated word found\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    if (find_first_repeated_word(test2, result, sizeof(result)) != NULL) {
        if (printf("First repeated word: %s\n", result) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("No repeated word found\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}