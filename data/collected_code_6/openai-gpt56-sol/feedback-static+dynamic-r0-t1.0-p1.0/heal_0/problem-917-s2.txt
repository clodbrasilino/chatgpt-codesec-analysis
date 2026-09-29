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

            if (fwrite(start, 1U, (size_t)(p - start), stdout) !=
                    (size_t)(p - start) ||
                fputc('\n', stdout) == EOF) {
                return -1;
            }
        } else {
            ++p;
        }
    }

    return 0;
}

int main(int argc, char *argv[])
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