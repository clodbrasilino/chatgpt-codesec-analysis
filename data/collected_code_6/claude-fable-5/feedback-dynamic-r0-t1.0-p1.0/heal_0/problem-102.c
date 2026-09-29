#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *snake_to_camel(const char *snake)
{
    size_t len;
    size_t i;
    size_t j;
    char *camel;
    int capitalize_next;

    if (snake == NULL) {
        return NULL;
    }

    len = strlen(snake);
    camel = malloc(len + 1);
    if (camel == NULL) {
        return NULL;
    }

    capitalize_next = 0;
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

int main(void)
{
    const char *input = "hello_world_example";
    char *result;

    result = snake_to_camel(input);
    if (result == NULL) {
        fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }

    if (printf("Input:  %s\n", input) < 0) {
        free(result);
        return EXIT_FAILURE;
    }
    if (printf("Output: %s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}