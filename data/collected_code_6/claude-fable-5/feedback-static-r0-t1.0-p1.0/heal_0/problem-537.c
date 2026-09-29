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

char *first_repeated_word(const char *str)
{
    char (*words)[MAX_WORD_LEN];
    char current[MAX_WORD_LEN];
    size_t pos = 0;
    size_t count = 0;
    size_t i;
    char *result = NULL;

    if (str == NULL) {
        return NULL;
    }

    words = malloc(MAX_WORDS * sizeof(*words));
    if (words == NULL) {
        return NULL;
    }

    while (extract_word(str, &pos, current, sizeof(current)) == 1) {
        for (i = 0; i < count; i++) {
            if (strcmp(words[i], current) == 0) {
                result = malloc(strlen(current) + 1);
                if (result != NULL) {
                    memcpy(result, current, strlen(current) + 1);
                }
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
    return NULL;
}

int main(void)
{
    const char *test1 = "the quick brown fox jumps over the lazy dog";
    const char *test2 = "hello world foo bar";
    const char *test3 = "one two two three";
    char *repeated;

    repeated = first_repeated_word(test1);
    if (repeated != NULL) {
        if (printf("First repeated word: %s\n", repeated) < 0) {
            free(repeated);
            return EXIT_FAILURE;
        }
        free(repeated);
    } else {
        if (printf("No repeated word found\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    repeated = first_repeated_word(test2);
    if (repeated != NULL) {
        if (printf("First repeated word: %s\n", repeated) < 0) {
            free(repeated);
            return EXIT_FAILURE;
        }
        free(repeated);
    } else {
        if (printf("No repeated word found\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    repeated = first_repeated_word(test3);
    if (repeated != NULL) {
        if (printf("First repeated word: %s\n", repeated) < 0) {
            free(repeated);
            return EXIT_FAILURE;
        }
        free(repeated);
    } else {
        if (printf("No repeated word found\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}