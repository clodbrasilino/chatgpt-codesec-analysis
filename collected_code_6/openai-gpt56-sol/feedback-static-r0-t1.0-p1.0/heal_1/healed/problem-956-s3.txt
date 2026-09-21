#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int write_part(const char *data, size_t length)
{
    if (length > 0 && fwrite(data, 1, length, stdout) != length) {
        return EXIT_FAILURE;
    }

    if (fputc('\n', stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

static int split_at_uppercase(const char *input)
{
    const unsigned char *cursor;
    const unsigned char *part;

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    cursor = (const unsigned char *)input;
    part = cursor;

    while (*cursor != '\0') {
        if (*cursor >= (unsigned char)'A' && *cursor <= (unsigned char)'Z') {
            if (cursor > part &&
                write_part((const char *)part, (size_t)(cursor - part)) !=
                    EXIT_SUCCESS) {
                return EXIT_FAILURE;
            }

            part = cursor;
            do {
                ++cursor;
            } while (*cursor >= (unsigned char)'A' &&
                     *cursor <= (unsigned char)'Z');

            if (write_part((const char *)part, (size_t)(cursor - part)) !=
                EXIT_SUCCESS) {
                return EXIT_FAILURE;
            }

            part = cursor;
        } else {
            ++cursor;
        }
    }

    if (cursor > part &&
        write_part((const char *)part, (size_t)(cursor - part)) !=
            EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }

    return ferror(stdout) ? EXIT_FAILURE : EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        const char *program = argc > 0 && argv[0] != NULL ? argv[0] : "program";
        fprintf(stderr, "Usage: %s <string>\n", program);
        return EXIT_FAILURE;
    }

    return split_at_uppercase(argv[1]);
}