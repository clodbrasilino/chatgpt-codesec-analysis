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
        if (isupper(c) != 0) {
            if (i > 0U) {
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
    output[j] = '\0';

    return output;
}

int main(void)
{
    char buffer[MAX_INPUT_LEN];
    int status = EXIT_SUCCESS;

    while (fgets(buffer, (int)sizeof(buffer), stdin) != NULL) {
        char *result;
        size_t len = strnlen(buffer, sizeof(buffer));

        while (len > 0U && (buffer[len - 1U] == '\n' || buffer[len - 1U] == '\r')) {
            buffer[len - 1U] = '\0';
            len--;
        }

        result = camel_to_snake(buffer);
        if (result == NULL) {
            (void)fprintf(stderr, "Conversion failed for input: %s\n", buffer);
            status = EXIT_FAILURE;
        } else {
            if (printf("%s\n", result) < 0) {
                status = EXIT_FAILURE;
            }
            free(result);
        }
    }

    return status;
}