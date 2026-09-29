#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_INPUT_LEN 255U

static char *remove_even_chars(const char *input, size_t max_len);

static char *remove_even_chars(const char *input, size_t max_len)
{
    size_t len;
    size_t i;
    size_t j;
    char *result;

    if (input == NULL) {
        return NULL;
    }

    len = strnlen(input, max_len);

    if (len >= (SIZE_MAX - 1U)) {
        return NULL;
    }

    result = (char *)malloc(len + 1U);
    if (result == NULL) {
        return NULL;
    }

    j = 0U;
    for (i = 0U; i < len; i++) {
        if ((i % 2U) != 0U) {
            result[j] = input[i];
            j++;
        }
    }
    result[j] = '\0';

    return result;
}

int main(void)
{
    char buffer[MAX_INPUT_LEN + 1U];
    char *output;
    size_t len;

    (void)memset(buffer, 0, sizeof(buffer));

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        (void)fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1U] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    if ((len > 0U) && (buffer[len - 1U] == '\n')) {
        buffer[len - 1U] = '\0';
    }

    output = remove_even_chars(buffer, sizeof(buffer));
    if (output == NULL) {
        (void)fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", output) < 0) {
        free(output);
        return EXIT_FAILURE;
    }

    free(output);
    return EXIT_SUCCESS;
}