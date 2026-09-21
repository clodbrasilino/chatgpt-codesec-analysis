#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 255U

char *remove_even_chars(const char *input)
{
    size_t len;
    size_t i;
    size_t j;
    char *result;

    if (input == NULL) {
        return NULL;
    }

    len = strnlen(input, MAX_INPUT_LEN + 1);
    if (len > MAX_INPUT_LEN) {
        return NULL;
    }

    result = malloc(len / 2 + 1);
    if (result == NULL) {
        return NULL;
    }

    j = 0;
    for (i = 0; i < len; i++) {
        if (i % 2 != 0) {
            result[j] = input[i];
            j++;
        }
    }
    result[j] = '\0';

    return result;
}

int main(void)
{
    char *buffer;
    char *output;
    size_t len;

    buffer = calloc(MAX_INPUT_LEN + 1, sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Enter a string: ");
    if (fgets(buffer, (int)(MAX_INPUT_LEN + 1), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    buffer[MAX_INPUT_LEN] = '\0';

    len = strnlen(buffer, MAX_INPUT_LEN + 1);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    output = remove_even_chars(buffer);
    if (output == NULL) {
        fprintf(stderr, "Error processing string\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    printf("Result: %s\n", output);

    free(output);
    free(buffer);

    return EXIT_SUCCESS;
}