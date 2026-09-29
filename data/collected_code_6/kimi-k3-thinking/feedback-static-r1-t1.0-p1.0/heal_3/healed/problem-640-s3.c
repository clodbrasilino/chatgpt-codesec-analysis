#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

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

static char *read_line(FILE *stream, size_t *out_len)
{
    char *buffer;
    size_t size;
    size_t len;
    int ch;

    size = 64;
    len = 0;

    buffer = (char *)malloc(size);
    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        ch = fgetc(stream);

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (len + 1 >= size) {
            size_t new_size;
            char *tmp;

            if (size > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }
            new_size = size * 2;

            tmp = (char *)realloc(buffer, new_size);
            if (tmp == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = tmp;
            size = new_size;
        }

        buffer[len] = (char)ch;
        len++;
    }

    if (ferror(stream)) {
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
        input = NULL;
        return EXIT_FAILURE;
    }

    printf("Result: %s\n", cleaned);

    free(cleaned);
    cleaned = NULL;
    free(input);
    input = NULL;

    return EXIT_SUCCESS;
}