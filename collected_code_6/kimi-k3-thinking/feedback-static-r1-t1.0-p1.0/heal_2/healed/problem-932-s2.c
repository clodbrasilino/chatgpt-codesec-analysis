#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 4096

static char *duplicate_string(const char *src)
{
    size_t len;
    char *copy;
    int written;

    if (src == NULL) {
        return NULL;
    }

    len = strnlen(src, MAX_STRING_LENGTH);
    if (len == MAX_STRING_LENGTH) {
        return NULL;
    }
    len += 1;

    copy = malloc(len);
    if (copy == NULL) {
        return NULL;
    }

    written = snprintf(copy, len, "%s", src);
    if (written < 0 || (size_t)written >= len) {
        free(copy);
        return NULL;
    }

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

static char **copy_strings(const char *input[], size_t input_count)
{
    char **words;
    size_t i;
    size_t j;

    if (input == NULL || input_count == 0 || input_count > SIZE_MAX / sizeof(*words)) {
        return NULL;
    }

    words = malloc(input_count * sizeof(*words));
    if (words == NULL) {
        return NULL;
    }

    for (i = 0; i < input_count; i++) {
        words[i] = duplicate_string(input[i]);
        if (words[i] == NULL) {
            for (j = 0; j < i; j++) {
                free(words[j]);
            }
            free(words);
            return NULL;
        }
    }

    return words;
}

int main(void)
{
    const char *input[] = {"apple", "banana", "apple", "cherry", "banana", "date"};
    size_t input_count = sizeof(input) / sizeof(input[0]);
    char **words;
    size_t unique_count;
    size_t i;

    words = copy_strings(input, input_count);
    if (words == NULL) {
        fprintf(stderr, "Failed to build word list\n");
        return EXIT_FAILURE;
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