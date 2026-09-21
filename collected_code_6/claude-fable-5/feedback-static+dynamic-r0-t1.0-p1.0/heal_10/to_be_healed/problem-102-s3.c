#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT 1024

char *snake_to_camel(const char *snake, size_t max_len)
{
    size_t len;
    size_t i;
    size_t j;
    int capitalize_next;
    char *camel;

    if (snake == NULL || max_len == 0) {
        return NULL;
    }

    len = 0;
    while (len < max_len && snake[len] != '\0') {
        len++;
    }

    camel = malloc(len + 1);
    if (camel == NULL) {
        return NULL;
    }

    j = 0;
    i = 0;
    capitalize_next = 1;
    while (i < len) {
        if (snake[i] == '_') {
            capitalize_next = 1;
            i++;
        } else {
            if (capitalize_next) {
                camel[j] = (char)toupper((unsigned char)snake[i]);
                capitalize_next = 0;
            } else {
                camel[j] = snake[i];
            }
            j++;
            i++;
        }
    }
    camel[j] = '\0';

    return camel;
}

static char *read_line(FILE *stream)
{
    size_t capacity;
    size_t length;
    char *buffer;
    char *tmp;
    int ch;

    if (stream == NULL) {
        return NULL;
    }

    capacity = MAX_INPUT;
    length = 0;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (length + 1 >= capacity) {
            if (capacity > (size_t)-1 / 2) {
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
        buffer[length] = (char)ch;
        length++;
    }

    if (length == 0 && ch == EOF) {
        free(buffer);
        return NULL;
    }

    while (length > 0 && (buffer[length - 1] == '\r' || buffer[length - 1] == '\n')) {
        length--;
    }

    buffer[length] = '\0';
    return buffer;
}

static size_t bounded_length(const char *str, size_t max_len)
{
    size_t len;

    len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

int main(void)
{
    char *input;
    char *result;
    size_t len;

    input = read_line(stdin);
    if (input == NULL) {
        fprintf(stderr, "Failed to read input\n");
        return EXIT_FAILURE;
    }

    len = bounded_length(input, (size_t)-1 - 1);

    result = snake_to_camel(input, len + 1);
    if (result == NULL) {
        fprintf(stderr, "Conversion failed\n");
        free(input);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        free(input);
        return EXIT_FAILURE;
    }

    free(result);
    free(input);
    return EXIT_SUCCESS;
}