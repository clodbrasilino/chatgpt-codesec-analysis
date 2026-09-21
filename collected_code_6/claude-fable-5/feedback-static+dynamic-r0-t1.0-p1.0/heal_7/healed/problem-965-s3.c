#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

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
    if (len > ((SIZE_MAX - 1U) / 2U)) {
        return NULL;
    }

    output = malloc((len * 2U) + 1U);
    if (output == NULL) {
        return NULL;
    }

    j = 0U;
    for (i = 0U; i < len; i++) {
        unsigned char c = (unsigned char)input[i];
        if (isupper(c) != 0) {
            if ((i > 0U) && (j > 0U) && (output[j - 1U] != '_')) {
                output[j] = '_';
                j++;
            }
            output[j] = (char)tolower(c);
            j++;
        } else if ((isspace(c) != 0) || (c == (unsigned char)'-')) {
            if ((j > 0U) && (output[j - 1U] != '_')) {
                output[j] = '_';
                j++;
            }
        } else {
            output[j] = (char)c;
            j++;
        }
    }
    output[j] = '\0';

    return output;
}

static char *read_input_line(void)
{
    size_t capacity = MAX_INPUT_LEN + 2U;
    size_t len = 0U;
    int ch;
    char *buffer;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    while ((ch = fgetc(stdin)) != EOF) {
        if ((ch == '\n') || (ch == '\r')) {
            break;
        }
        if (len >= (capacity - 1U)) {
            break;
        }
        buffer[len] = (char)ch;
        len++;
    }

    if ((len == 0U) && (ch == EOF)) {
        free(buffer);
        return NULL;
    }

    buffer[len] = '\0';
    return buffer;
}

int main(int argc, char *argv[])
{
    const char *source;
    char *input_line = NULL;
    char *result;

    if (argc > 1) {
        source = argv[1];
    } else {
        input_line = read_input_line();
        if (input_line == NULL) {
            (void)fprintf(stderr, "No input provided\n");
            return EXIT_FAILURE;
        }
        source = input_line;
    }

    result = camel_to_snake(source);
    if (result == NULL) {
        (void)fprintf(stderr, "Conversion failed\n");
        free(input_line);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        free(input_line);
        return EXIT_FAILURE;
    }

    if (fflush(stdout) != 0) {
        free(result);
        free(input_line);
        return EXIT_FAILURE;
    }

    free(result);
    free(input_line);
    return EXIT_SUCCESS;
}