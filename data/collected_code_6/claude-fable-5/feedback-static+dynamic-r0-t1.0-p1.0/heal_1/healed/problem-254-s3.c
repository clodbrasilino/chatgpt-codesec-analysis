#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static char *duplicate_string(const char *src, size_t len)
{
    char *dest = malloc(len + 1);
    if (dest == NULL) {
        return NULL;
    }
    memcpy(dest, src, len);
    dest[len] = '\0';
    return dest;
}

char **find_words(const char *input, size_t *count)
{
    char *copy = NULL;
    char **results = NULL;
    char **temp = NULL;
    char *token = NULL;
    char *saveptr = NULL;
    size_t capacity = 8;
    size_t input_len;
    size_t token_len;
    size_t i;

    if (input == NULL || count == NULL) {
        return NULL;
    }

    *count = 0;

    input_len = strlen(input);
    copy = duplicate_string(input, input_len);
    if (copy == NULL) {
        return NULL;
    }

    results = malloc(capacity * sizeof(char *));
    if (results == NULL) {
        free(copy);
        return NULL;
    }

    token = strtok_r(copy, " \t\n\r.,;:!?", &saveptr);
    while (token != NULL) {
        char first = (char)tolower((unsigned char)token[0]);
        if (first == 'a' || first == 'e') {
            if (*count == capacity) {
                if (capacity > SIZE_MAX / 2 / sizeof(char *)) {
                    for (i = 0; i < *count; i++) {
                        free(results[i]);
                    }
                    free(results);
                    free(copy);
                    *count = 0;
                    return NULL;
                }
                capacity *= 2;
                temp = realloc(results, capacity * sizeof(char *));
                if (temp == NULL) {
                    for (i = 0; i < *count; i++) {
                        free(results[i]);
                    }
                    free(results);
                    free(copy);
                    *count = 0;
                    return NULL;
                }
                results = temp;
            }
            token_len = strlen(token);
            results[*count] = duplicate_string(token, token_len);
            if (results[*count] == NULL) {
                for (i = 0; i < *count; i++) {
                    free(results[i]);
                }
                free(results);
                free(copy);
                *count = 0;
                return NULL;
            }
            (*count)++;
        }
        token = strtok_r(NULL, " \t\n\r.,;:!?", &saveptr);
    }

    free(copy);
    return results;
}

void free_words(char **words, size_t count)
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

int main(void)
{
    const char *text = "An apple and an egg were eaten by everyone at the event.";
    char **words = NULL;
    size_t count = 0;
    size_t i;

    words = find_words(text, &count);
    if (words == NULL && count == 0) {
        if (printf("No matching words found or an error occurred.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    if (printf("Words starting with 'a' or 'e':\n") < 0) {
        free_words(words, count);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        if (printf("%s\n", words[i]) < 0) {
            free_words(words, count);
            return EXIT_FAILURE;
        }
    }

    free_words(words, count);
    return EXIT_SUCCESS;
}