#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define MAX_INPUT_LEN 4096

static char *duplicate_string(const char *src)
{
    size_t len;
    size_t dest_size;
    char *dest;

    if (src == NULL) {
        return NULL;
    }

    len = strnlen(src, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
        return NULL;
    }

    dest_size = len + 1;
    dest = malloc(dest_size);
    if (dest == NULL) {
        return NULL;
    }

    if (len >= dest_size) {
        free(dest);
        return NULL;
    }

    memcpy(dest, src, len);
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
    size_t n;

    if (input == NULL || count == NULL) {
        return NULL;
    }

    *count = 0;
    capacity = 8;
    n = 0;

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
            if (n == capacity) {
                if (capacity > SIZE_MAX / (2 * sizeof(char *))) {
                    for (size_t i = 0; i < n; i++) {
                        free(results[i]);
                    }
                    free(results);
                    free(copy);
                    return NULL;
                }
                capacity *= 2;
                temp = realloc(results, capacity * sizeof(char *));
                if (temp == NULL) {
                    for (size_t i = 0; i < n; i++) {
                        free(results[i]);
                    }
                    free(results);
                    free(copy);
                    return NULL;
                }
                results = temp;
            }
            results[n] = duplicate_string(token);
            if (results[n] == NULL) {
                for (size_t i = 0; i < n; i++) {
                    free(results[i]);
                }
                free(results);
                free(copy);
                return NULL;
            }
            n++;
        }
        token = strtok_r(NULL, " \t\n\r.,;:!?", &saveptr);
    }

    free(copy);
    *count = n;
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
    const char *text = "An apple and an egg are on every table each evening";
    size_t count = 0;
    char **words = find_words(text, &count);

    if (words == NULL) {
        fprintf(stderr, "Failed to process input\n");
        return EXIT_FAILURE;
    }

    printf("Words starting with 'a' or 'e':\n");
    for (size_t i = 0; i < count; i++) {
        printf("%s\n", words[i]);
    }

    free_words(words, count);
    return EXIT_SUCCESS;
}