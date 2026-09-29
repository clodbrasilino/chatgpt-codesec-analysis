#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *duplicate_string(const char *src)
{
    size_t len;
    char *copy;

    if (src == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(src) + 1;
    copy = malloc(len);
    if (copy == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, src, len);
    return copy;
}

static int is_duplicate(char **words, size_t count, const char *word)
{
    size_t i;

    for (i = 0; i < count; i++) {
        if (words[i] != NULL && strcmp(words[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

size_t remove_duplicate_words(char **words, size_t count)
{
    size_t unique_count = 0;
    size_t i;

    if (words == NULL) {
        return 0;
    }

    for (i = 0; i < count; i++) {
        if (words[i] == NULL) {
            continue;
        }
        if (is_duplicate(words, unique_count, words[i])) {
            free(words[i]);
            words[i] = NULL;
        } else {
            words[unique_count] = words[i];
            if (unique_count != i) {
                words[i] = NULL;
            }
            unique_count++;
        }
    }

    return unique_count;
}

int main(void)
{
    const char *input[] = {"apple", "banana", "apple", "cherry", "banana", "date"};
    size_t input_count = sizeof(input) / sizeof(input[0]);
    char **words;
    size_t unique_count;
    size_t i;
    size_t j;

    words = malloc(input_count * sizeof(*words));
    if (words == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < input_count; i++) {
        words[i] = duplicate_string(input[i]);
        if (words[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            for (j = 0; j < i; j++) {
                free(words[j]);
            }
            free(words);
            return EXIT_FAILURE;
        }
    }

    unique_count = remove_duplicate_words(words, input_count);

    for (i = 0; i < unique_count; i++) {
        printf("%s\n", words[i]);
    }

    for (i = 0; i < input_count; i++) {
        free(words[i]);
    }
    free(words);

    return EXIT_SUCCESS;
}