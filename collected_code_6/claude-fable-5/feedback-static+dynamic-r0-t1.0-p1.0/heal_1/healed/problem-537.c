#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1024
#define MAX_WORD_LEN 256

static char *duplicate_string(const char *src)
{
    size_t len;
    char *copy;

    if (src == NULL) {
        return NULL;
    }

    len = strlen(src);
    copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, src, len);
    copy[len] = '\0';
    return copy;
}

static int extract_word(const char *str, size_t *pos, char *word, size_t word_size)
{
    size_t i = *pos;
    size_t w = 0;

    if (str == NULL || pos == NULL || word == NULL || word_size == 0) {
        return 0;
    }

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

char *first_repeated_word(const char *str)
{
    char (*words)[MAX_WORD_LEN];
    char current[MAX_WORD_LEN];
    size_t pos = 0;
    size_t count = 0;
    size_t i;
    size_t len;
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
            len = strlen(current);
            if (len >= MAX_WORD_LEN) {
                len = MAX_WORD_LEN - 1;
            }
            memcpy(words[count], current, len);
            words[count][len] = '\0';
            count++;
        } else {
            break;
        }
    }

    free(words);
    return duplicate_string("None");
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

    if (strcmp(repeated, "None") == 0) {
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