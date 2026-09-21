#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1024
#define MAX_WORD_LEN 256
#define MAX_INPUT_LEN 65536

static int extract_words(const char *str, size_t max_len,
                         char words[][MAX_WORD_LEN], int max_words)
{
    int count = 0;
    size_t i = 0;
    size_t len;

    if (str == NULL || words == NULL || max_words <= 0) {
        return 0;
    }

    len = strnlen(str, max_len);

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
    char (*words)[MAX_WORD_LEN];
    const char *found = NULL;
    int count;
    int i;
    int j;

    if (str == NULL || result == NULL || result_size == 0) {
        return NULL;
    }

    words = calloc(MAX_WORDS, sizeof(*words));
    if (words == NULL) {
        return NULL;
    }

    count = extract_words(str, MAX_INPUT_LEN, words, MAX_WORDS);

    for (i = 1; i < count && found == NULL; i++) {
        for (j = 0; j < i; j++) {
            if (strncmp(words[i], words[j], MAX_WORD_LEN) == 0) {
                size_t wlen = strnlen(words[i], MAX_WORD_LEN);
                if (wlen >= result_size) {
                    free(words);
                    return NULL;
                }
                memcpy(result, words[i], wlen);
                result[wlen] = '\0';
                found = result;
                break;
            }
        }
    }

    free(words);
    return found;
}

int main(void)
{
    const char *test1 = "he had had quite enough of this nonsense";
    const char *test2 = "one two three four";
    char result[MAX_WORD_LEN];

    memset(result, 0, sizeof(result));

    if (find_first_repeated_word(test1, result, sizeof(result)) != NULL) {
        if (printf("First repeated word: %s\n", result) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("No repeated word found\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    memset(result, 0, sizeof(result));

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