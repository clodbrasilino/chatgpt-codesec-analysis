#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got <no output>
  *  test case 2 failed: expected ['Red &', 'Orange+', 'Green', 'Orange', 'White'], got <no output>
  *  test case 1 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got <no output>
  */

char **remove_words(const char **words, size_t count, const char *pattern, size_t *out_count)
{
    char **result = NULL;
    size_t kept = 0;
    size_t i;

    if (words == NULL || pattern == NULL || out_count == NULL) {
        return NULL;
    }

    result = malloc(count * sizeof(char *));
    if (result == NULL && count > 0) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        if (words[i] == NULL) {
            continue;
        }
        if (strstr(words[i], pattern) == NULL) {
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

static char *read_line(FILE *fp)
{
    char buffer[4096];
    size_t len;
    char *line;

    if (fgets(buffer, sizeof(buffer), fp) == NULL) {
        return NULL;
    }
    len = strlen(buffer);
    while (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r')) {
        buffer[--len] = '\0';
    }
    line = malloc(len + 1);
    if (line == NULL) {
        return NULL;
    }
    memcpy(line, buffer, len + 1);
    return line;
}

int main(void)
{
    char *count_line;
    char **input_words;
    char *pattern;
    char **filtered;
    size_t count;
    size_t result_count = 0;
    size_t i;

    count_line = read_line(stdin);
    if (count_line == NULL) {
        fprintf(stderr, "Failed to read word count\n");
        return EXIT_FAILURE;
    }
    count = (size_t)strtoul(count_line, NULL, 10);
    free(count_line);

    input_words = malloc(count * sizeof(char *));
    if (input_words == NULL && count > 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        input_words[i] = read_line(stdin);
        if (input_words[i] == NULL) {
            size_t j;
            for (j = 0; j < i; j++) {
                free(input_words[j]);
            }
            free(input_words);
            fprintf(stderr, "Failed to read word\n");
            return EXIT_FAILURE;
        }
    }

    pattern = read_line(stdin);
    if (pattern == NULL) {
        for (i = 0; i < count; i++) {
            free(input_words[i]);
        }
        free(input_words);
        fprintf(stderr, "Failed to read pattern\n");
        return EXIT_FAILURE;
    }

    filtered = remove_words((const char **)input_words, count, pattern, &result_count);
    if (filtered == NULL && count > 0) {
        for (i = 0; i < count; i++) {
            free(input_words[i]);
        }
        free(input_words);
        free(pattern);
        fprintf(stderr, "Failed to filter word list\n");
        return EXIT_FAILURE;
    }

    printf("[");
    for (i = 0; i < result_count; i++) {
        printf("'%s'", filtered[i]);
        if (i + 1 < result_count) {
            printf(", ");
        }
    }
    printf("]\n");

    free_word_list(filtered, result_count);
    for (i = 0; i < count; i++) {
        free(input_words[i]);
    }
    free(input_words);
    free(pattern);

    return EXIT_SUCCESS;
}