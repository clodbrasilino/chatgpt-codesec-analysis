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

int main(void)
{
    char input[MAX_INPUT];
    char *result;
    size_t len;

    memset(input, 0, sizeof(input));

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Failed to read input\n");
        return EXIT_FAILURE;
    }

    input[sizeof(input) - 1] = '\0';

    len = 0;
    while (len < sizeof(input) && input[len] != '\0') {
        len++;
    }

    while (len > 0 && (input[len - 1] == '\n' || input[len - 1] == '\r')) {
        input[len - 1] = '\0';
        len--;
    }

    result = snake_to_camel(input, sizeof(input));
    if (result == NULL) {
        fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}