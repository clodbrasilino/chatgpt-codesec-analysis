#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH ((size_t)1048576)

static size_t max_uppercase_run(const char *str)
{
    size_t max_run = 0;
    size_t current_run = 0;

    if (str == NULL) {
        return 0;
    }

    while (*str != '\0') {
        if (isupper((unsigned char)*str)) {
            ++current_run;
            if (current_run > max_run) {
                max_run = current_run;
            }
        } else {
            current_run = 0;
        }
        ++str;
    }

    return max_run;
}

int main(void)
{
    char *input = malloc(MAX_INPUT_LENGTH + 2U);
    size_t length;

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    if (fgets(input, (int)(MAX_INPUT_LENGTH + 2U), stdin) == NULL) {
        int status = ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
        free(input);
        return status;
    }

    length = 0;
    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (length > MAX_INPUT_LENGTH) {
        int ch;

        do {
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        free(input);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", max_uppercase_run(input)) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}