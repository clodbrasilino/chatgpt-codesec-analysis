#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1024
#define MAX_WORD_LEN 256

static int extract_word(const char *str, size_t *pos, char *word, size_t word_size)
{
    size_t i = *pos;
    size_t w = 0;

    while (str[i] != '\0' && !isalnum((unsigned char)str[i])) {
        i++;
    }

    if (str[i] == '\0') {
        *pos = i;
        return 0;
    }

    while (str[i] != '\0' && isalnum((unsigned char)str[i])) {
        if (w < word_size - 1) {
            word[w] = str[i];
            w++;
        }
        i++;
    }

    word[w] = '\0';
    *pos = i;
    return 1;
}

static char *duplicate_string(const char *src)
{
    size_t len;
    char *copy;

    if (src == NULL) {
        return NULL;
    }

    len = strlen(src);
    copy = malloc(len + 1);
    if (copy != NULL) {
        memcpy(copy, src, len + 1);
    }
    return copy;
}

char *first_repeated_word(const char *str)
{
    char (*words)[MAX_WORD_LEN];
    char current[MAX_WORD_LEN];
    size_t pos = 0;
    size_t count = 0;
    size_t i;
    char *result;

    if (str == NULL) {
        return duplicate_string("None");
    }

    words = malloc(MAX_WORDS * sizeof(*words));
    if (words == NULL) {
        return NULL;
    }

    while (extract_word(str, &pos, current, sizeof(current)) == 1) {
        for (i = 0; i < count; i++) {
            if (strcmp(words[i], current) == 0) {
                result = duplicate_string(current);
                free(words);
                return result;
            }
        }
        if (count < MAX_WORDS) {
            strncpy(words[count], current, MAX_WORD_LEN - 1);
            words[count][MAX_WORD_LEN - 1] = '\0';
            count++;
        } else {
            break;
        }
    }

    free(words);
    return duplicate_string("None");
}

int main(void)
{
    const char *tests[] = {
        "the quick brown fox jumps over the lazy dog",
        "hello world foo bar",
        "one two two three"
    };
    size_t num_tests = sizeof(tests) / sizeof(tests[0]);
    size_t i;
    char *repeated;

    for (i = 0; i < num_tests; i++) {
        repeated = first_repeated_word(tests[i]);
        if (repeated == NULL) {
            if (printf("Memory allocation failed\n") < 0) {
                return EXIT_FAILURE;
            }
            return EXIT_FAILURE;
        }
        if (strcmp(repeated, "None") == 0) {
            if (printf("No repeated word found\n") < 0) {
                free(repeated);
                return EXIT_FAILURE;
            }
        } else {
            if (printf("First repeated word: %s\n", repeated) < 0) {
                free(repeated);
                return EXIT_FAILURE;
            }
        }
        free(repeated);
    }

    return EXIT_SUCCESS;
}