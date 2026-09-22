#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRING_LENGTH 4096
#define MAX_WORDS 1024
#define DEFAULT_EXTRACT_SIZE 6

void free_strings(char **strings, size_t count)
{
    size_t i;

    if (strings == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        free(strings[i]);
    }
    free(strings);
}

static size_t bounded_strlen(const char *s, size_t max_len)
{
    size_t len = 0;

    while (len < max_len && s[len] != '\0') {
        len++;
    }

    return len;
}

char **extract_strings(const char *const *strings, size_t count, size_t size, size_t *out_count)
{
    char **result;
    size_t i;
    size_t extracted;

    if (out_count == NULL) {
        return NULL;
    }

    *out_count = 0;

    if (strings == NULL || count == 0) {
        return NULL;
    }

    result = calloc(count, sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    extracted = 0;

    for (i = 0; i < count; i++) {
        size_t len;

        if (strings[i] == NULL) {
            continue;
        }

        len = bounded_strlen(strings[i], MAX_STRING_LENGTH);

        if (len == MAX_STRING_LENGTH || len < size) {
            continue;
        }

        result[extracted] = malloc(len + 1);
        if (result[extracted] == NULL) {
            free_strings(result, count);
            *out_count = 0;
            return NULL;
        }

        snprintf(result[extracted], len + 1, "%s", strings[i]);

        extracted++;
    }

    *out_count = extracted;

    return result;
}

static int is_number(const char *s)
{
    size_t i;

    if (s == NULL || s[0] == '\0') {
        return 0;
    }

    for (i = 0; s[i] != '\0'; i++) {
        if (!isdigit((unsigned char)s[i])) {
            return 0;
        }
    }

    return 1;
}

static void trim_token(char *s)
{
    size_t start = 0;
    size_t end;
    size_t len;

    if (s == NULL) {
        return;
    }

    len = strlen(s);

    while (start < len && !isalnum((unsigned char)s[start])) {
        start++;
    }

    end = len;
    while (end > start && !isalnum((unsigned char)s[end - 1])) {
        end--;
    }

    if (start > 0 && end > start) {
        memmove(s, s + start, end - start);
    }

    s[end - start] = '\0';
}

int main(void)
{
    char *words[MAX_WORDS];
    size_t word_count = 0;
    size_t extract_size = DEFAULT_EXTRACT_SIZE;
    int seen_word = 0;
    char token[MAX_STRING_LENGTH + 2];
    char **extracted;
    size_t extracted_count = 0;
    size_t i;
    size_t len;

    while (word_count < MAX_WORDS && scanf("%4096s", token) == 1) {
        trim_token(token);

        if (token[0] == '\0') {
            continue;
        }

        if (!seen_word && is_number(token)) {
            unsigned long value = strtoul(token, NULL, 10);
            if (value > 0 && value < MAX_STRING_LENGTH) {
                extract_size = (size_t)value;
            }
            continue;
        }

        seen_word = 1;

        len = strlen(token);
        words[word_count] = malloc(len + 1);
        if (words[word_count] == NULL) {
            free_strings(words, word_count);
            fprintf(stderr, "Out of memory\n");
            return EXIT_FAILURE;
        }
        memcpy(words[word_count], token, len + 1);
        word_count++;
    }

    if (word_count == 0) {
        return EXIT_SUCCESS;
    }

    extracted = extract_strings((const char *const *)words, word_count, extract_size, &extracted_count);
    if (extracted == NULL) {
        free_strings(words, word_count);
        fprintf(stderr, "Failed to extract strings\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < extracted_count; i++) {
        if (extracted[i] != NULL) {
            printf("%s\n", extracted[i]);
        }
    }

    free_strings(extracted, word_count);
    free_strings(words, word_count);

    return EXIT_SUCCESS;
}