#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define INITIAL_LINE_CAPACITY 64
#define MAX_LINE_LENGTH (1024UL * 1024UL)

static size_t bounded_strlen(const char *str, size_t max_len)
{
    size_t len;

    len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

char *remove_parenthesis_area(const char *str, size_t max_len)
{
    char *result;
    size_t i;
    size_t j;
    size_t len;
    int depth;

    if (str == NULL) {
        return NULL;
    }

    len = bounded_strlen(str, max_len);
    result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    depth = 0;
    j = 0;
    for (i = 0; i < len; i++) {
        if (str[i] == '(') {
            depth++;
        } else if (str[i] == ')') {
            if (depth > 0) {
                depth--;
            }
        } else if (depth == 0) {
            result[j] = str[i];
            j++;
        }
    }
    result[j] = '\0';

    return result;
}

static int grow_buffer(char **buffer, size_t *size)
{
    size_t new_size;
    char *tmp;

    if (buffer == NULL || *buffer == NULL || size == NULL) {
        return -1;
    }

    if (*size > SIZE_MAX / 2 || *size >= MAX_LINE_LENGTH) {
        return -1;
    }

    new_size = *size * 2;
    if (new_size > MAX_LINE_LENGTH) {
        new_size = MAX_LINE_LENGTH;
    }

    if (new_size <= *size) {
        return -1;
    }

    tmp = (char *)realloc(*buffer, new_size);
    if (tmp == NULL) {
        return -1;
    }

    *buffer = tmp;
    *size = new_size;
    return 0;
}

static char *read_line(FILE *stream, size_t *out_len)
{
    char *buffer;
    size_t size;
    size_t len;

    if (stream == NULL) {
        return NULL;
    }

    size = INITIAL_LINE_CAPACITY;
    len = 0;

    buffer = (char *)malloc(size);
    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        int ch;

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (len + 1 >= size) {
            if (grow_buffer(&buffer, &size) != 0) {
                free(buffer);
                return NULL;
            }
        }

        if (len + 1 >= size) {
            free(buffer);
            return NULL;
        }

        buffer[len] = (char)ch;
        len++;
    }

    if (ferror(stream)) {
        free(buffer);
        return NULL;
    }

    if (len >= size) {
        free(buffer);
        return NULL;
    }
    buffer[len] = '\0';

    if (out_len != NULL) {
        *out_len = len;
    }

    return buffer;
}

int main(void)
{
    char *input;
    char *cleaned;
    size_t input_len;

    printf("Enter a string: ");
    fflush(stdout);

    input_len = 0;
    input = read_line(stdin, &input_len);
    if (input == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    cleaned = remove_parenthesis_area(input, input_len);
    if (cleaned == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(input);
        return EXIT_FAILURE;
    }

    printf("Result: %s\n", cleaned);

    free(cleaned);
    free(input);

    return EXIT_SUCCESS;
}