#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int is_lowercase_letter(unsigned char c)
{
    return c >= (unsigned char)'a' && c <= (unsigned char)'z';
}

static void find_sequences(const char *text)
{
    size_t i = 0;

    while (text[i] != '\0') {
        size_t start;
        size_t end;
        int has_underscore = 0;

        if (!is_lowercase_letter((unsigned char)text[i])) {
            ++i;
            continue;
        }

        start = i;

        while (is_lowercase_letter((unsigned char)text[i])) {
            ++i;
        }

        while (text[i] == '_' &&
               is_lowercase_letter((unsigned char)text[i + 1])) {
            has_underscore = 1;
            ++i;

            while (is_lowercase_letter((unsigned char)text[i])) {
                ++i;
            }
        }

        end = i;

        if (has_underscore) {
            if (fwrite(text + start, 1, end - start, stdout) != end - start ||
                fputc('\n', stdout) == EOF) {
                fprintf(stderr, "Output error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <text>\n", argv[0]);
        return EXIT_FAILURE;
    }

    find_sequences(argv[1]);

    if (fflush(stdout) == EOF) {
        fprintf(stderr, "Output error\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}