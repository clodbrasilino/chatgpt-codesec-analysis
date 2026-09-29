#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <inttypes.h>
#include <ctype.h>

#define INPUT_SIZE 128U
#define OCTAL_BUFFER_SIZE ((sizeof(uintmax_t) * 8U + 2U) / 3U + 1U)

static int decimal_to_octal(uintmax_t value, char *buffer, size_t size)
{
    int result;

    if (buffer == NULL || size < OCTAL_BUFFER_SIZE) {
        return -1;
    }

    result = snprintf(buffer, size, "%jo", value);
    if (result < 0 || (size_t)result >= size) {
        return -1;
    }

    return 0;
}

int main(void)
{
    char input[INPUT_SIZE];
    char output[OCTAL_BUFFER_SIZE];
    char *end;
    uintmax_t value;
    size_t length;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    length = 0U;
    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] != '\n' && !feof(stdin)) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    value = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input) {
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    if (decimal_to_octal(value, output, sizeof(output)) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%s\n", output) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}