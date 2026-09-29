#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1024
#define MAX_WORD_LEN 256

static size_t bounded_length(const char *s, size_t max_len)
{
    size_t n = 0;
    while (n < max_len && s[n] != '\0') {
        n++;
    }
    return n;
}

static int extract_words(const char *str, char **words, int max_words, size_t word_len)
{
    int count = 0;
    size_t i = 0;

    if (str == NULL || words == NULL || max_words <= 0 || word_len == 0) {
        return 0;
    }

    while (str[i] != '\0' && count < max_words) {
        while (str[i] != '\0' && !isalnum((unsigned char)str[i])) {
            i++;
        }
        if (str[i] == '\0') {
            break;
        }

        words[count] = calloc(word_len, sizeof(char));
        if (words[count] == NULL) {
            return count;
        }

        size_t w = 0;
        while (str[i] != '\0' && isalnum((unsigned char)str[i])) {
            if (w < word_len - 1) {
                words[count][w] = (char)tolower((unsigned char)str[i]);
                w++;
            }
            i++;
        }
        words[count][w] = '\0';
        count++;
    }
    return count;
}

static void free_words(char **words, int count)
{
    int i;

    if (words == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        free(words[i]);
        words[i] = NULL;
    }
    free(words);
}

const char *find_first_repeated_word(const char *str, char *result, size_t result_size)
{
    char **words;
    int count;
    int i;
    int j;

    if (str == NULL || result == NULL || result_size == 0) {
        return NULL;
    }

    words = calloc(MAX_WORDS, sizeof(char *));
    if (words == NULL) {
        return NULL;
    }

    count = extract_words(str, words, MAX_WORDS, MAX_WORD_LEN);

    for (i = 1; i < count; i++) {
        for (j = 0; j < i; j++) {
            if (words[i] != NULL && words[j] != NULL &&
                strncmp(words[i], words[j], MAX_WORD_LEN) == 0) {
                size_t len = bounded_length(words[i], MAX_WORD_LEN);
                if (len >= result_size) {
                    free_words(words, count);
                    return NULL;
                }
                memcpy(result, words[i], len);
                result[len] = '\0';
                free_words(words, count);
                return result;
            }
        }
    }

    free_words(words, count);
    return NULL;
}

int main(void)
{
    const char *test1 = "he had had quite enough of this nonsense";
    const char *test2 = "one two three four";
    char *result;

    result = calloc(MAX_WORD_LEN, sizeof(char));
    if (result == NULL) {
        return EXIT_FAILURE;
    }

    if (find_first_repeated_word(test1, result, MAX_WORD_LEN) != NULL) {
        if (printf("First repeated word: %s\n", result) < 0) {
            free(result);
            return EXIT_FAILURE;
        }
    } else {
        if (printf("No repeated word found\n") < 0) {
            free(result);
            return EXIT_FAILURE;
        }
    }

    memset(result, 0, MAX_WORD_LEN);

    if (find_first_repeated_word(test2, result, MAX_WORD_LEN) != NULL) {
        if (printf("First repeated word: %s\n", result) < 0) {
            free(result);
            return EXIT_FAILURE;
        }
    } else {
        if (printf("No repeated word found\n") < 0) {
            free(result);
            return EXIT_FAILURE;
        }
    }

    free(result);
    return EXIT_SUCCESS;
}