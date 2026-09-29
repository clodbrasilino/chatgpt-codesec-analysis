#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1024
#define MAX_WORD_LEN 256
#define MAX_INPUT_LEN 65536

static char *duplicate_string(const char *src, size_t max_len)
{
    size_t len;
    char *copy;

    if (src == NULL || max_len == 0) {
        return NULL;
    }

    len = strnlen(src, max_len - 1);
    copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }

    if (len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, src, len);
    }
    copy[len] = '\0';
    return copy;
}

static int extract_word(const char *str, size_t str_len, size_t *pos,
                        char *word, size_t word_size)
{
    size_t i;
    size_t w = 0;

    if (str == NULL || pos == NULL || word == NULL || word_size == 0) {
        return 0;
    }

    i = *pos;

    while (i < str_len && str[i] != '\0' && !isalnum((unsigned char)str[i])) {
        i++;
    }

    if (i >= str_len || str[i] == '\0') {
        *pos = i;
        word[0] = '\0';
        return 0;
    }

    while (i < str_len && str[i] != '\0' && isalnum((unsigned char)str[i])) {
        if (w + 1 < word_size) {
            word[w] = str[i];
            w++;
        }
        i++;
    }

    word[w] = '\0';
    *pos = i;
    return 1;
}

char *first_repeated_word(const char *str)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char (*words)[MAX_WORD_LEN];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char current[MAX_WORD_LEN];
    size_t pos = 0;
    size_t count = 0;
    size_t i;
    size_t len;
    size_t str_len;
    char *result;

    if (str == NULL) {
        return duplicate_string("None", MAX_WORD_LEN);
    }

    str_len = strnlen(str, MAX_INPUT_LEN);

    words = calloc((size_t)MAX_WORDS, sizeof(*words));
    if (words == NULL) {
        return NULL;
    }

    while (extract_word(str, str_len, &pos, current, sizeof(current)) == 1) {
        for (i = 0; i < count; i++) {
            if (strncmp(words[i], current, MAX_WORD_LEN) == 0) {
                result = duplicate_string(current, MAX_WORD_LEN);
                free(words);
                return result;
            }
        }
        if (count < MAX_WORDS) {
            len = strnlen(current, sizeof(current));
            if (len > MAX_WORD_LEN - 1) {
                len = MAX_WORD_LEN - 1;
            }
            if (len > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(words[count], current, len);
            }
            words[count][len] = '\0';
            count++;
        } else {
            break;
        }
    }

    free(words);
    return duplicate_string("None", MAX_WORD_LEN);
}

static int run_test(const char *input)
{
    char *repeated;

    repeated = first_repeated_word(input);
    if (repeated == NULL) {
        if (printf("Memory allocation failure\n") < 0) {
            return -1;
        }
        return -1;
    }

    if (strncmp(repeated, "None", MAX_WORD_LEN) == 0) {
        if (printf("No repeated word found\n") < 0) {
            free(repeated);
            return -1;
        }
    } else {
        if (printf("First repeated word: %s\n", repeated) < 0) {
            free(repeated);
            return -1;
        }
    }

    free(repeated);
    return 0;
}

int main(void)
{
    const char *test1 = "the quick brown fox jumps over the lazy dog";
    const char *test2 = "hello world foo bar";
    const char *test3 = "one two two three";

    if (run_test(test1) != 0) {
        return EXIT_FAILURE;
    }

    if (run_test(test2) != 0) {
        return EXIT_FAILURE;
    }

    if (run_test(test3) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}