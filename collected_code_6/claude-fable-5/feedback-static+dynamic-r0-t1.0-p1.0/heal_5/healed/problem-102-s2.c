#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LEN 4096

static char *snake_to_camel(const char *snake)
{
    size_t len;
    size_t i;
    size_t j;
    char *camel;
    int capitalize_next;

    if (snake == NULL) {
        return NULL;
    }

    len = strnlen(snake, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
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
                camel[j] = snake[i];
            }
            j++;
        }
    }
    camel[j] = '\0';

    return camel;
}

int main(void)
{
    char *input;
    char *result;
    size_t len;

    input = calloc(MAX_INPUT_LEN, sizeof(char));
    if (input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (fgets(input, MAX_INPUT_LEN, stdin) == NULL) {
        fprintf(stderr, "No input provided\n");
        free(input);
        return EXIT_FAILURE;
    }

    input[MAX_INPUT_LEN - 1] = '\0';

    len = strnlen(input, MAX_INPUT_LEN);

    while (len > 0 && (input[len - 1] == '\n' || input[len - 1] == '\r')) {
        input[len - 1] = '\0';
        len--;
    }

    result = snake_to_camel(input);
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