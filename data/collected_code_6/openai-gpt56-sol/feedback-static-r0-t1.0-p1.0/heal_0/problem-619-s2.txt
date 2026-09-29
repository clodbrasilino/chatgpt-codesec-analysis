#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int move_digits_to_end(char *str)
{
    size_t length;
    char *result;
    size_t write_index = 0;

    if (str == NULL) {
        return -1;
    }

    length = strlen(str);

    if (length == SIZE_MAX) {
        return -1;
    }

    result = malloc(length + 1);
    if (result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        if (!isdigit((unsigned char)str[i])) {
            result[write_index++] = str[i];
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (isdigit((unsigned char)str[i])) {
            result[write_index++] = str[i];
        }
    }

    result[write_index] = '\0';
    memcpy(str, result, length + 1);
    free(result);

    return 0;
}

int main(void)
{
    char input[1024];

    if (fgets(input, sizeof(input), stdin) == NULL) {
        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    size_t length = strlen(input);
    if (length > 0 && input[length - 1] == '\n') {
        input[length - 1] = '\0';
    } else if (!feof(stdin)) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        return EXIT_FAILURE;
    }

    if (move_digits_to_end(input) != 0) {
        return EXIT_FAILURE;
    }

    if (puts(input) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}