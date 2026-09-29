#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *move_numbers_to_end(const char *input)
{
    size_t len;
    char *result;
    size_t i;
    size_t pos = 0;

    if (input == NULL) {
        return NULL;
    }

    len = strlen(input);
    result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < len; i++) {
        if (!isdigit((unsigned char)input[i])) {
            result[pos] = input[i];
            pos++;
        }
    }

    for (i = 0; i < len; i++) {
        if (isdigit((unsigned char)input[i])) {
            result[pos] = input[i];
            pos++;
        }
    }

    result[pos] = '\0';
    return result;
}

int main(void)
{
    const char *test = "a1b2c3d4e5";
    char *output;

    output = move_numbers_to_end(test);
    if (output == NULL) {
        fprintf(stderr, "Failed to process string\n");
        return EXIT_FAILURE;
    }

    if (printf("Input:  %s\n", test) < 0) {
        free(output);
        return EXIT_FAILURE;
    }

    if (printf("Output: %s\n", output) < 0) {
        free(output);
        return EXIT_FAILURE;
    }

    free(output);
    return EXIT_SUCCESS;
}