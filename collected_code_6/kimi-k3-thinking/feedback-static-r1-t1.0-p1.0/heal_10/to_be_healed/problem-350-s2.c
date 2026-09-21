#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define CHAR_SET_SIZE 256
#define INITIAL_LINE_CAPACITY 128

static char find_most_frequent_char(const char *str, size_t len)
{
    size_t freq[CHAR_SET_SIZE] = {0};
    char most_frequent = '\0';
    size_t max_count = 0;
    size_t i;

    if (str == NULL || len == 0) {
        return '\0';
    }

    for (i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (freq[c] < SIZE_MAX) {
            freq[c]++;
        }
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

static int grow_buffer(char **buffer, size_t *capacity, size_t required)
{
    size_t new_capacity;
    char *tmp;

    if (buffer == NULL || capacity == NULL || *buffer == NULL) {
        return -1;
    }

    if (required == 0 || required > SIZE_MAX / 2 + 1) {
        return -1;
    }

    new_capacity = *capacity;

    if (new_capacity == 0) {
        new_capacity = INITIAL_LINE_CAPACITY;
    }

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            return -1;
        }
        new_capacity *= 2;
    }

    if (new_capacity == *capacity) {
        return 0;
    }

    tmp = (char *)realloc(*buffer, new_capacity);
    if (tmp == NULL) {
        return -1;
    }

    *buffer = tmp;
    *capacity = new_capacity;

    return 0;
}

static char *read_line(FILE *stream, size_t *out_len)
{
    size_t capacity = INITIAL_LINE_CAPACITY;
    size_t length = 0;
    char *buffer;
    int ch;

    if (stream == NULL) {
        return NULL;
    }

    if (INITIAL_LINE_CAPACITY < 2) {
        return NULL;
    }

    buffer = (char *)malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (length >= SIZE_MAX - 2) {
            free(buffer);
            return NULL;
        }

        if (length + 1 >= capacity) {
            if (grow_buffer(&buffer, &capacity, length + 2) != 0) {
                free(buffer);
                return NULL;
            }
            if (length + 1 >= capacity) {
                free(buffer);
                return NULL;
            }
        }

        buffer[length] = (char)ch;
        length++;
    }

    if (ferror(stream)) {
        free(buffer);
        return NULL;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return NULL;
    }

    if (length >= capacity) {
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