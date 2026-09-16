#include <stdio.h>
#include <stdlib.h>

static int is_lowercase_letter(unsigned char c)
{
    return c >= (unsigned char)'a' && c <= (unsigned char)'z';
}

static int find_sequences(const char *text)
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
                return -1;
            }
        }
    }

    return 0;
}

int main(int argc, char *const argv[])
{
    const char *const program_name = argv[0];
    const char *const text = argc > 1 ? argv[1] : NULL;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <text>\n", program_name);
        return EXIT_FAILURE;
    }

    if (find_sequences(text) != 0 || fflush(stdout) == EOF) {
        fprintf(stderr, "Output error\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}