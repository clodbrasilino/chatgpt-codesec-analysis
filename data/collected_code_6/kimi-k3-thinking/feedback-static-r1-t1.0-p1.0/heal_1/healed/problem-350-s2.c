#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define CHAR_SET_SIZE 256

static char find_most_frequent_char(const char *str, size_t len)
{
    size_t freq[CHAR_SET_SIZE] = {0};
    char most_frequent = '\0';
    size_t max_count = 0;
    size_t i;

    if (str == NULL || len == 0) {
        return '\0';
    }

    most_frequent = str[0];

    for (i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        freq[c]++;
        if (freq[c] > max_count) {
            max_count = freq[c];
            most_frequent = (char)c;
        }
    }
    return most_frequent;
}

char *minimize_string(const char *str, size_t len, size_t *out_len)
{
    char *result;
    char target;
    size_t i;
    size_t j = 0;

    if (str == NULL) {
        return NULL;
    }

    if (len == SIZE_MAX) {
        return NULL;
    }

    result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    if (len == 0) {
        result[0] = '\0';
        if (out_len != NULL) {
            *out_len = 0;
        }
        return result;
    }

    target = find_most_frequent_char(str, len);

    for (i = 0; i < len; i++) {
        if (str[i] != target) {
            result[j] = str[i];
            j++;
        }
    }
    result[j] = '\0';

    if (out_len != NULL) {
        *out_len = j;
    }

    return result;
}

static char *read_line(FILE *stream, size_t *out_len)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer;
    int ch;

    buffer = (char *)malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *tmp;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }
            new_capacity = capacity * 2;

            tmp = (char *)realloc(buffer, new_capacity);
            if (tmp == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = tmp;
            capacity = new_capacity;
        }
        buffer[length] = (char)ch;
        length++;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';

    if (out_len != NULL) {
        *out_len = length;
    }

    return buffer;
}

int main(void)
{
    char *buffer;
    char *minimized;
    size_t len = 0;
    size_t minimized_len = 0;

    printf("Enter a string: ");
    fflush(stdout);

    buffer = read_line(stdin, &len);
    if (buffer == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    if (len == 0) {
        fprintf(stderr, "Empty string provided\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    minimized = minimize_string(buffer, len, &minimized_len);
    if (minimized == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    printf("Minimized string: %s\n", minimized);
    printf("Original length: %zu\n", len);
    printf("Minimized length: %zu\n", minimized_len);

    free(minimized);
    minimized = NULL;
    free(buffer);
    buffer = NULL;

    return EXIT_SUCCESS;
}