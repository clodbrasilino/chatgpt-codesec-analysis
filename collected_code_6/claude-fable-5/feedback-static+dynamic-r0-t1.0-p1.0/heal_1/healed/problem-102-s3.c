#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *snake_to_camel(const char *snake)
{
    size_t len;
    size_t i;
    size_t j;
    int capitalize_next;
    char *camel;

    if (snake == NULL) {
        return NULL;
    }

    len = strlen(snake);
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
    const char *input = "hello_world_example_string";
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