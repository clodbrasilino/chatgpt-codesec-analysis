#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

static int is_numeric(const char *s)
{
    size_t i = 0;

    if (s == NULL || s[0] == '\0') {
        return 0;
    }
    if (s[0] == '+' || s[0] == '-') {
        i = 1;
        if (s[1] == '\0') {
            return 0;
        }
    }
    for (; s[i] != '\0'; i++) {
        if (!isdigit((unsigned char)s[i])) {
            return 0;
        }
    }
    return 1;
}

static char *duplicate_string(const char *s)
{
    size_t len;
    char *copy;

    if (s == NULL) {
        return NULL;
    }
    len = strlen(s) + 1;
    copy = malloc(len);
    if (copy == NULL) {
        return NULL;
    }
    memcpy(copy, s, len);
    return copy;
}

static void free_string_array(char **arr, size_t n)
{
    size_t i;

    if (arr == NULL) {
        return;
    }
    for (i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);
}

static char **increment_numeric_strings(const char *const *input, size_t n, long k)
{
    char **result;
    size_t i;

    if (input == NULL || n == 0) {
        return NULL;
    }
    result = calloc(n, sizeof(char *));
    if (result == NULL) {
        return NULL;
    }
    for (i = 0; i < n; i++) {
        if (input[i] == NULL) {
            free_string_array(result, i);
            return NULL;
        }
        if (is_numeric(input[i])) {
            long value;
            char *endptr;
            char buffer[64];
            int written;

            errno = 0;
            value = strtol(input[i], &endptr, 10);
            if (errno == ERANGE || endptr == input[i] || *endptr != '\0') {
                free_string_array(result, i);
                return NULL;
            }
            if ((k > 0 && value > LONG_MAX - k) ||
                (k < 0 && value < LONG_MIN - k)) {
                free_string_array(result, i);
                return NULL;
            }
            value += k;
            written = snprintf(buffer, sizeof(buffer), "%ld", value);
            if (written < 0 || (size_t)written >= sizeof(buffer)) {
                free_string_array(result, i);
                return NULL;
            }
            result[i] = duplicate_string(buffer);
        } else {
            result[i] = duplicate_string(input[i]);
        }
        if (result[i] == NULL) {
            free_string_array(result, i);
            return NULL;
        }
    }
    return result;
}

static char *read_line(FILE *fp)
{
    size_t capacity = 128;
    size_t length = 0;
    char *line;
    int c;

    if (fp == NULL) {
        return NULL;
    }
    line = malloc(capacity);
    if (line == NULL) {
        return NULL;
    }
    while ((c = fgetc(fp)) != EOF && c != '\n') {
        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *tmp;

            if (capacity > SIZE_MAX / 2) {
                free(line);
                return NULL;
            }
            new_capacity = capacity * 2;
            tmp = realloc(line, new_capacity);
            if (tmp == NULL) {
                free(line);
                return NULL;
            }
            line = tmp;
            capacity = new_capacity;
        }
        line[length++] = (char)c;
    }
    if (length == 0 && c == EOF) {
        free(line);
        return NULL;
    }
    while (length > 0 && (line[length - 1] == '\r' || line[length - 1] == ' ')) {
        length--;
    }
    line[length] = '\0';
    return line;
}

static char **split_tokens(const char *line, size_t *out_count)
{
    char **tokens = NULL;
    size_t count = 0;
    size_t capacity = 0;
    size_t i = 0;

    if (line == NULL || out_count == NULL) {
        return NULL;
    }
    while (line[i] != '\0') {
        size_t start;
        size_t token_len;
        char *token;

        while (line[i] == ' ' || line[i] == '\t' ||
               line[i] == '\r' || line[i] == '\n') {
            i++;
        }
        if (line[i] == '\0') {
            break;
        }
        start = i;
        while (line[i] != '\0' && line[i] != ' ' && line[i] != '\t' &&
               line[i] != '\r' && line[i] != '\n') {
            i++;
        }
        token_len = i - start;
        if (count >= capacity) {
            size_t new_capacity = (capacity == 0) ? 8 : capacity * 2;
            char **tmp;

            if (new_capacity > SIZE_MAX / sizeof(char *)) {
                free_string_array(tokens, count);
                return NULL;
            }
            tmp = realloc(tokens, new_capacity * sizeof(char *));
            if (tmp == NULL) {
                free_string_array(tokens, count);
                return NULL;
            }
            tokens = tmp;
            capacity = new_capacity;
        }
        token = malloc(token_len + 1);
        if (token == NULL) {
            free_string_array(tokens, count);
            return NULL;
        }
        memcpy(token, line + start, token_len);
        token[token_len] = '\0';
        tokens[count] = token;
        count++;
    }
    *out_count = count;
    return tokens;
}

int main(void)
{
    char *strings_line;
    char *k_line;
    char **tokens;
    size_t count = 0;
    long k;
    char *endptr;
    char **updated;
    size_t i;

    strings_line = read_line(stdin);
    if (strings_line == NULL) {
        fprintf(stderr, "Failed to read input strings\n");
        return EXIT_FAILURE;
    }
    k_line = read_line(stdin);
    if (k_line == NULL) {
        free(strings_line);
        fprintf(stderr, "Failed to read increment value\n");
        return EXIT_FAILURE;
    }
    errno = 0;
    k = strtol(k_line, &endptr, 10);
    if (errno == ERANGE || endptr == k_line) {
        free(strings_line);
        free(k_line);
        fprintf(stderr, "Invalid increment value\n");
        return EXIT_FAILURE;
    }
    free(k_line);
    tokens = split_tokens(strings_line, &count);
    free(strings_line);
    if (tokens == NULL || count == 0) {
        free_string_array(tokens, count);
        fprintf(stderr, "Failed to parse input strings\n");
        return EXIT_FAILURE;
    }
    updated = increment_numeric_strings((const char *const *)tokens, count, k);
    if (updated == NULL) {
        free_string_array(tokens, count);
        fprintf(stderr, "Failed to process strings\n");
        return EXIT_FAILURE;
    }
    for (i = 0; i < count; i++) {
        if (printf("%s%s", updated[i], (i + 1