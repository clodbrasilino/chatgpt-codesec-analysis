#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 4096U
#define INPUT_BUFFER_SIZE (MAX_INPUT_LENGTH + 2U)

static bool contains_only_allowed_characters(const char *string)
{
    const unsigned char *p = (const unsigned char *)string;

    if (string == NULL || *string == '\0') {
        return false;
    }

    while (*p != '\0') {
        if (!((*p >= (unsigned char)'A' && *p <= (unsigned char)'Z') ||
              (*p >= (unsigned char)'a' && *p <= (unsigned char)'z') ||
              (*p >= (unsigned char)'0' && *p <= (unsigned char)'9'))) {
            return false;
        }
        ++p;
    }

    return true;
}

static int discard_line(FILE *stream)
{
    int ch;

    while ((ch = fgetc(stream)) != '\n') {
        if (ch == EOF) {
            return ferror(stream) ? -1 : 0;
        }
    }

    return 0;
}

int main(void)
{
    char *input;
    size_t length;

    input = malloc(INPUT_BUFFER_SIZE);
    if (input == NULL) {
        fputs("Failed to allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fgets(input, (int)INPUT_BUFFER_SIZE, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            free(input);
            return EXIT_FAILURE;
        }

        puts("invalid");
        free(input);
        return EXIT_SUCCESS;
    }

    length = strcspn(input, "\n");

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (length > MAX_INPUT_LENGTH) {
        if (discard_line(stdin) != 0) {
            fputs("Failed to read input.\n", stderr);
        } else {
            fputs("Input is too large.\n", stderr);
        }

        free(input);
        return EXIT_FAILURE;
    } else {
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
                free(input);
                return EXIT_FAILURE;
            }
        } else if (ch != '\n') {
            if (discard_line(stdin) != 0) {
                fputs("Failed to read input.\n", stderr);
            } else {
                fputs("Input is too large.\n", stderr);
            }

            free(input);
            return EXIT_FAILURE;
        }
    }

    puts(contains_only_allowed_characters(input) ? "valid" : "invalid");

    free(input);
    return EXIT_SUCCESS;
}