#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

static char *duplicate_string(const char *src)
{
    size_t len;
    char *dest;

    if (src == NULL) {
        return NULL;
    }

    len = strnlen(src, SIZE_MAX - 1);
    if (len == SIZE_MAX - 1) {
        return NULL;
    }

    dest = malloc(len + 1);
    if (dest == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        dest[i] = src[i];
    }
    dest[len] = '\0';
    return dest;
}

char **find_words(const char *input, size_t *count)
{
    char *copy;
    char **results;
    char **temp;
    char *token;
    char *saveptr;
    size_t capacity;

    if (input == NULL || count == NULL) {
        return NULL;
    }

    *count = 0;
    capacity = 8;

    copy = duplicate_string(input);
    if (copy == NULL) {
        return NULL;
    }

    results = malloc(capacity * sizeof(char *));
    if (results == NULL) {
        free(copy);
        return NULL;
    }

    saveptr = NULL;
    token = strtok_r(copy, " \t\n\r.,;:!?", &saveptr);
    while (token != NULL) {
        char first = (char)tolower((unsigned char)token[0]);
        if (first == 'a' || first == 'e') {
            if (*count == capacity) {
                if (capacity > SIZE_MAX / (2 * sizeof(char *))) {
                    for (size_t i = 0; i < *count; i++) {
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
                    for (size_t i = 0; i < *count; i++) {
                        free(results[i]);
                    }
                    free(results);
                    free(copy);
                    *count = 0;
                    return NULL;
                }
                results = temp;
            }
            results[*count] = duplicate_string(token);
            if (results[*count] == NULL) {
                for (size_t i = 0; i < *count; i++) {
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
    if (words == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
}

int main(void)
{
    const char *text = "An apple and an egg were eaten by everyone at the event.";
    size_t count = 0;
    char **words;

    words = find_words(text, &count);
    if (words == NULL) {
        fprintf(stderr, "Error: could not process the string\n");
        return EXIT_FAILURE;
    }

    printf("Words starting with 'a' or 'e':\n");
    for (size_t i = 0; i < count; i++) {
        printf("%s\n", words[i]);
    }

    free_words(words, count);
    return EXIT_SUCCESS;
}