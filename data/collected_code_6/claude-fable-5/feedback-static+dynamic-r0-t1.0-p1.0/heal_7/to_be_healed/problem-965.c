#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LEN 4096U

char *camel_to_snake(const char *input)
{
    size_t len;
    size_t i;
    size_t j;
    char *output;

    if (input == NULL) {
        return NULL;
    }

    len = strnlen(input, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
        return NULL;
    }

    output = malloc((len * 2U) + 1U);
    if (output == NULL) {
        return NULL;
    }

    j = 0U;
    for (i = 0U; i < len; i++) {
        unsigned char c = (unsigned char)input[i];
        if (isspace(c) != 0) {
            if (j > 0U && output[j - 1U] != '_') {
                output[j] = '_';
                j++;
            }
        } else if (isupper(c) != 0) {
            if (j > 0U && output[j - 1U] != '_') {
                output[j] = '_';
                j++;
            }
            output[j] = (char)tolower(c);
            j++;
        } else {
            output[j] = (char)c;
            j++;
        }
    }

    while (j > 0U && output[j - 1U] == '_') {
        j--;
    }
    output[j] = '\0';

    return output;
}

static int process_input(const char *input)
{
    char *result;

    result = camel_to_snake(input);
    if (result == NULL) {
        (void)fprintf(stderr, "Conversion failed for input: %s\n", input);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    char *buffer;
    int status = EXIT_SUCCESS;

    if (argc > 1) {
        int i;
        for (i = 1; i < argc; i++) {
            if (process_input(argv[i]) != EXIT_SUCCESS) {
                status = EXIT_FAILURE;
            }
        }
        return status;
    }

    buffer = malloc(MAX_INPUT_LEN);
    if (buffer == NULL) {
        (void)fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    while (fgets(buffer, (int)MAX_INPUT_LEN, stdin) != NULL) {
        size_t len = strnlen(buffer, MAX_INPUT_LEN);

        while (len > 0U && (buffer[len - 1U] == '\n' || buffer[len - 1U] == '\r')) {
            buffer[len - 1U] = '\0';
            len--;
        }

        if (process_input(buffer) != EXIT_SUCCESS) {
            status = EXIT_FAILURE;
        }
    }

    free(buffer);
    return status;
}