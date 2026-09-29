#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static int find_sequences(const char *text)
{
    const unsigned char *p = (const unsigned char *)text;

    while (*p != '\0') {
        if (isupper(*p) && islower(p[1])) {
            const unsigned char *start = p++;

            while (islower(*p)) {
                ++p;
            }

            size_t length = (size_t)(p - start);

            if (fwrite(start, 1U, length, stdout) != length ||
                fputc('\n', stdout) == EOF) {
                return -1;
            }
        } else {
            ++p;
        }
    }

    return 0;
}

int main(int argc, const char *const argv[])
{
    int status = EXIT_SUCCESS;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <text> [text ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; ++i) {
        if (find_sequences(argv[i]) != 0) {
            status = EXIT_FAILURE;
            break;
        }
    }

    if (fflush(stdout) == EOF) {
        status = EXIT_FAILURE;
    }

    return status;
}