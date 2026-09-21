#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int remove_non_alnum(const char *input, size_t input_length, char **output)
{
    char *result;
    size_t destination = 0;

    if (output == NULL) {
        errno = EINVAL;
        return -1;
    }

    *output = NULL;

    if (input == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (input_length == SIZE_MAX) {
        errno = EOVERFLOW;
        return -1;
    }

    result = malloc(input_length + 1);
    if (result == NULL) {
        errno = ENOMEM;
        return -1;
    }

    for (size_t source = 0; source < input_length; ++source) {
        unsigned char character = (unsigned char)input[source];

        if (isalnum(character) != 0) {
            result[destination++] = (char)character;
        }
    }

    result[destination] = '\0';
    *output = result;
    return 0;
}

static int get_string_length(const char *string, size_t *length)
{
    size_t count = 0;

    if (string == NULL || length == NULL) {
        errno = EINVAL;
        return -1;
    }

    while (string[count] != '\0') {
        if (count == SIZE_MAX - 1) {
            errno = EOVERFLOW;
            return -1;
        }

        ++count;
    }

    *length = count;
    return 0;
}

int main(int argc, char *argv[])
{
    char *filtered = NULL;
    size_t input_length;

    if (argc != 2) {
        const char *program_name = argc > 0 && argv[0] != NULL
            ? argv[0]
            : "program";

        if (fprintf(stderr, "Usage: %s <text>\n", program_name) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if (get_string_length(argv[1], &input_length) != 0) {
        perror("get_string_length");
        return EXIT_FAILURE;
    }

    if (remove_non_alnum(argv[1], input_length, &filtered) != 0) {
        perror("remove_non_alnum");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", filtered) < 0) {
        free(filtered);
        return EXIT_FAILURE;
    }

    free(filtered);
    return EXIT_SUCCESS;
}