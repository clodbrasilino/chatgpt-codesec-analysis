#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_SIZE 1024

static char *snake_to_camel(const char *snake, size_t max_len)
{
    size_t len;
    size_t i;
    size_t j;
    char *camel;
    int capitalize_next;

    if (snake == NULL || max_len == 0) {
        return NULL;
    }

    len = strnlen(snake, max_len);
    if (len >= max_len) {
        return NULL;
    }

    camel = malloc(len + 1);
    if (camel == NULL) {
        return NULL;
    }

    capitalize_next = 1;
    j = 0;
    for (i = 0; i < len; i++) {
        if (snake[i] == '_') {
            capitalize_next = 1;
        } else {
            if (capitalize_next != 0) {
                camel[j] = (char)toupper((unsigned char)snake[i]);
                capitalize_next = 0;
            } else {
                camel[j] = (char)tolower((unsigned char)snake[i]);
            }
            j++;
        }
    }
    camel[j] = '\0';

    return camel;
}

static char *read_line(size_t max_size)
{
    char *buffer;
    size_t len;

    if (max_size == 0) {
        return NULL;
    }

    buffer = calloc(max_size, sizeof(char));
    if (buffer == NULL) {
        return NULL;
    }

    if (fgets(buffer, (int)max_size, stdin) == NULL) {
        free(buffer);
        return NULL;
    }

    buffer[max_size - 1] = '\0';

    len = strnlen(buffer, max_size);
    while (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r')) {
        buffer[len - 1] = '\0';
        len--;
    }

    return buffer;
}

int main(void)
{
    char *input;
    char *result;

    input = read_line(MAX_INPUT_SIZE);
    if (input == NULL) {
        fprintf(stderr, "No input provided\n");
        return EXIT_FAILURE;
    }

    result = snake_to_camel(input, MAX_INPUT_SIZE);
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

    if (fflush(stdout) != 0) {
        free(result);
        free(input);
        return EXIT_FAILURE;
    }

    free(result);
    free(input);
    return EXIT_SUCCESS;
}