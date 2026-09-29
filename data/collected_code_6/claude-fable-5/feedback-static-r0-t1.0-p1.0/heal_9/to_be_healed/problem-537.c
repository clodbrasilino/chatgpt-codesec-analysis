#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int extract_word(const char *str, size_t *pos, char **word, size_t *word_len)
{
    size_t i;
    size_t start;
    size_t len;
    char *buf;

    if (str == NULL || pos == NULL || word == NULL || word_len == NULL) {
        return 0;
    }

    i = *pos;

    while (str[i] != '\0' && !isalnum((unsigned char)str[i])) {
        i++;
    }

    if (str[i] == '\0') {
        *pos = i;
        return 0;
    }

    start = i;

    while (str[i] != '\0' && isalnum((unsigned char)str[i])) {
        i++;
    }

    len = i - start;

    buf = malloc(len + 1);
    if (buf == NULL) {
        *pos = i;
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buf, str + start, len);
    buf[len] = '\0';

    *word = buf;
    *word_len = len;
    *pos = i;
    return 1;
}

static char *duplicate_string(const char *src, size_t len)
{
    char *dst;

    if (src == NULL) {
        return NULL;
    }

    dst = malloc(len + 1);
    if (dst == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dst, src, len);
    dst[len] = '\0';
    return dst;
}

static void free_words(char **words, size_t count)
{
    size_t i;

    if (words == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
}

char *first_repeated_word(const char *str)
{
    char **words = NULL;
    char **tmp;
    size_t capacity = 0;
    size_t count = 0;
    size_t pos = 0;
    size_t current_len = 0;
    size_t i;
    char *current = NULL;
    char *result = NULL;

    if (str == NULL) {
        return NULL;
    }

    while (extract_word(str, &pos, &current, &current_len) == 1) {
        for (i = 0; i < count; i++) {
            if (strcmp(words[i], current) == 0) {
                result = duplicate_string(current, current_len);
                free(current);
                free_words(words, count);
                return result;
            }
        }

        if (count == capacity) {
            size_t new_capacity = (capacity == 0) ? 16 : capacity * 2;
            if (new_capacity <= capacity) {
                free(current);
                free_words(words, count);
                return NULL;
            }
            tmp = realloc(words, new_capacity * sizeof(*words));
            if (tmp == NULL) {
                free(current);
                free_words(words, count);
                return NULL;
            }
            words = tmp;
            capacity = new_capacity;
        }

        words[count] = current;
        count++;
        current = NULL;
    }

    free_words(words, count);
    return NULL;
}

static int report_result(char *repeated)
{
    if (repeated != NULL) {
        if (printf("First repeated word: %s\n", repeated) < 0) {
            free(repeated);
            return -1;
        }
        free(repeated);
    } else {
        if (printf("No repeated word found\n") < 0) {
            return -1;
        }
    }
    return 0;
}

int main(void)
{
    const char *test1 = "the quick brown fox jumps over the lazy dog";
    const char *test2 = "hello world foo bar";
    const char *test3 = "one two two three";

    if (report_result(first_repeated_word(test1)) != 0) {
        return EXIT_FAILURE;
    }

    if (report_result(first_repeated_word(test2)) != 0) {
        return EXIT_FAILURE;
    }

    if (report_result(first_repeated_word(test3)) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}