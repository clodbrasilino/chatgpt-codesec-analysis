#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char **remove_words(const char **words, size_t count, const char *pattern, size_t *out_count)
{
    char **result = NULL;
    size_t kept = 0;
    size_t i;

    if (words == NULL || pattern == NULL || out_count == NULL) {
        return NULL;
    }

    *out_count = 0;

    if (count > SIZE_MAX / sizeof(char *)) {
        return NULL;
    }

    result = malloc((count > 0 ? count : 1) * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        if (words[i] == NULL) {
            continue;
        }
        if (pattern[0] == '\0' || strstr(words[i], pattern) == NULL) {
            size_t len = strlen(words[i]) + 1;
            char *copy = malloc(len);
            if (copy == NULL) {
                size_t j;
                for (j = 0; j < kept; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            memcpy(copy, words[i], len);
            result[kept] = copy;
            kept++;
        }
    }

    *out_count = kept;
    return result;
}

void free_word_list(char **list, size_t count)
{
    size_t i;

    if (list == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        free(list[i]);
    }
    free(list);
}

static char *read_line(FILE *stream)
{
    size_t capacity = 64;
    size_t length = 0;
    int ch;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return NULL;
    }

    ch = fgetc(stream);
    if (ch == EOF) {
        free(buffer);
        return NULL;
    }

    while (ch != EOF && ch != '\n') {
        if (length + 1 >= capacity) {
            char *tmp;
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }
            capacity *= 2;
            tmp = realloc(buffer, capacity);
            if (tmp == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = tmp;
        }
        buffer[length++] = (char)ch;
        ch = fgetc(stream);
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        length--;
    }
    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *pattern = NULL;
    char **words = NULL;
    size_t count = 0;
    size_t capacity = 0;
    char *line = NULL;
    char **filtered = NULL;
    size_t result_count = 0;
    size_t i;

    pattern = read_line(stdin);
    if (pattern == NULL) {
        return EXIT_FAILURE;
    }

    while ((line = read_line(stdin)) != NULL) {
        if (count >= capacity) {
            char **tmp;
            size_t new_capacity = (capacity == 0) ? 8 : capacity * 2;
            if (new_capacity > SIZE_MAX / sizeof(char *)) {
                free(line);
                free(pattern);
                free_word_list(words, count);
                return EXIT_FAILURE;
            }
            tmp = realloc(words, new_capacity * sizeof(char *));
            if (tmp == NULL) {
                free(line);
                free(pattern);
                free_word_list(words, count);
                return EXIT_FAILURE;
            }
            words = tmp;
            capacity = new_capacity;
        }
        words[count++] = line;
    }

    filtered = remove_words((const char **)words, count, pattern, &result_count);
    if (filtered == NULL) {
        free(pattern);
        free_word_list(words, count);
        return EXIT_FAILURE;
    }

    for (i = 0; i < result_count; i++) {
        printf("%s\n", filtered[i]);
    }

    free_word_list(filtered, result_count);
    free_word_list(words, count);
    free(pattern);

    return EXIT_SUCCESS;
}