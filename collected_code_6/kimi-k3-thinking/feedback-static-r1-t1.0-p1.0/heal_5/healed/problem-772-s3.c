#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdint.h>

#define INPUT_BUFFER_SIZE 1024
#define MAX_PROCESSED_LENGTH 4096
#define MAX_DISCARD_CHARS 8192
#define LENGTH_BUFFER_SIZE 32

static size_t safe_strnlen(const char *s, size_t max_len)
{
    size_t n = 0;

    if (s == NULL) {
        return 0;
    }

    while (n < max_len && s[n] != '\0') {
        n++;
    }

    return n;
}

static size_t safe_copy(char *dst, size_t dst_capacity, size_t dst_offset,
                        const char *src, size_t count)
{
    size_t idx = 0;

    if (dst == NULL || src == NULL) {
        return 0;
    }
    if (dst_offset > dst_capacity || count > dst_capacity - dst_offset) {
        return 0;
    }

    while (idx < count) {
        dst[dst_offset + idx] = src[idx];
        idx++;
    }

    return idx;
}

static void discard_excess_input(size_t max_chars)
{
    size_t discarded = 0;
    int ch;

    while (discarded < max_chars) {
        ch = getchar();
        if (ch == EOF || ch == '\n') {
            break;
        }
        discarded++;
    }
}

char *remove_words_of_length(const char *str, size_t k)
{
    size_t len;
    size_t i = 0;
    size_t j = 0;
    int first_word = 1;
    char *result;
    char *shrunk;

    if (str == NULL) {
        return NULL;
    }

    len = safe_strnlen(str, MAX_PROCESSED_LENGTH + 1);
    if (len > MAX_PROCESSED_LENGTH) {
        return NULL;
    }

    result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    while (i < len) {
        size_t word_start;
        size_t word_len;

        while (i < len && isspace((unsigned char)str[i])) {
            i++;
        }
        if (i >= len) {
            break;
        }

        word_start = i;
        while (i < len && !isspace((unsigned char)str[i])) {
            i++;
        }
        word_len = i - word_start;

        if (word_len != k) {
            size_t needed = word_len + (first_word ? (size_t)0 : (size_t)1);

            if (j > len || needed > len - j) {
                free(result);
                return NULL;
            }
            if (!first_word) {
                result[j++] = ' ';
            }
            if (word_len > 0) {
                if (safe_copy(result, len + 1, j, str + word_start, word_len) != word_len) {
                    free(result);
                    return NULL;
                }
                j += word_len;
            }
            first_word = 0;
        }
    }
    result[j] = '\0';

    shrunk = (char *)realloc(result, j + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

int main(void)
{
    char *input = NULL;
    char *length_input = NULL;
    size_t k = 0;
    size_t input_len;
    const char *p;
    char *end = NULL;
    unsigned long long value;
    char *modified = NULL;
    int status = EXIT_FAILURE;

    input = (char *)malloc(INPUT_BUFFER_SIZE);
    if (input == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    length_input = (char *)malloc(LENGTH_BUFFER_SIZE);
    if (length_input == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(input);
        return EXIT_FAILURE;
    }

    printf("Enter a string: ");
    if (fgets(input, INPUT_BUFFER_SIZE, stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        goto cleanup;
    }

    input_len = safe_strnlen(input, INPUT_BUFFER_SIZE);

    if (input_len > 0 && input[input_len - 1] == '\n') {
        input[input_len - 1] = '\0';
    } else if (input_len == INPUT_BUFFER_SIZE - 1) {
        discard_excess_input(MAX_DISCARD_CHARS);
        fprintf(stderr, "Input exceeds the maximum allowed length.\n");
        goto cleanup;
    }

    printf("Enter the word length to remove: ");
    if (fgets(length_input, LENGTH_BUFFER_SIZE, stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        goto cleanup;
    }

    p = length_input;
    while (isspace((unsigned char)*p)) {
        p++;
    }
    if (*p == '-' || *p == '\0') {
        fprintf(stderr, "Invalid length value.\n");
        goto cleanup;
    }

    errno = 0;
    value = strtoull(p, &end, 10);
    if (errno != 0 || end == p) {
        fprintf(stderr, "Invalid length value.\n");
        goto cleanup;
    }
    while (*end != '\0') {
        if (!isspace((unsigned char)*end)) {
            fprintf(stderr, "Invalid length value.\n");
            goto cleanup;
        }
        end++;
    }
    if (value > (unsigned long long)SIZE_MAX) {
        fprintf(stderr, "Invalid length value.\n");
        goto cleanup;
    }
    k = (size_t)value;

    modified = remove_words_of_length(input, k);
    if (modified == NULL) {
        fprintf(stderr, "Failed to process the string.\n");
        goto cleanup;
    }

    printf("Result: \"%s\"\n", modified);

    free(modified);
    status = EXIT_SUCCESS;

cleanup:
    free(input);
    free(length_input);
    return status;
}