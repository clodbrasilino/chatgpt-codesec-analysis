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

static void strip_trailing_newlines(char *s)
{
    size_t len;

    len = strnlen(s, MAX_INPUT_LEN);
    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r')) {
        s[len - 1] = '\0';
        len--;
    }
}

int main(int argc, char *argv[])
{
    char *input;
    char *result;

    input = calloc(MAX_INPUT_LEN, sizeof(char));
    if (input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (argc > 1 && argv[1] != NULL) {
        if (strnlen(argv[1], MAX_INPUT_LEN) >= MAX_INPUT_LEN) {
            fprintf(stderr, "Input too long\n");
            free(input);
            return EXIT_FAILURE;
        }
        strncpy(input, argv[1], MAX_INPUT_LEN - 1);
        input[MAX_INPUT_LEN - 1] = '\0';
    } else {
        if (fgets(input, MAX_INPUT_LEN, stdin) == NULL) {
            fprintf(stderr, "No input provided\n");
            free(input);
            return EXIT_FAILURE;
        }
        input[MAX_INPUT_LEN - 1] = '\0';
    }

    strip_trailing_newlines(input);

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

    if (fflush(stdout) != 0) {
        free(result);
        free(input);
        return EXIT_FAILURE;
    }

    free(result);
    free(input);
    return EXIT_SUCCESS;
}